"""{name}

    Usage:
        {name} [options]

    Options:
        -h, --help                                  Show this screen
        -v, --version                               Show version
        -t <threshold>, --threshold=<threshold>     Score threshold [default: 50]
"""


import collections
import docopt
import glob
import os
import re
import sys


Unit = collections.namedtuple(
    "Unit", ["header", "template", "source", "test"], defaults=[None, None, None, None],
)


def get_unit_score(unit):
    score = 0

    if not unit.header and not unit.template and not unit.source and not unit.test:
        return 0

    if unit.test:
        return 5

    if unit.header:
        score += 1

    if unit.template:
        score += 2 if not unit.source else 1

    if unit.source:
        score += 2

    return score


if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

    arguments = docopt.docopt(
        __doc__.format(name="check_analysis"), version="check_analysis 1.0"
    )

    folders = ["include", "src", "test", "vendor"]
    extensions = ["*.hpp", "*.tpp", "*.cpp"]
    globs = [
        "{folder}/**/{extension}".format(folder=f, extension=e)
        for f in folders
        for e in extensions
    ]
    files = [
        f for g in globs for f in glob.glob(g, recursive=True) if os.path.isfile(f)
    ]

    headers = [f for f in files if f.endswith(".hpp")]
    templates = [f for f in files if f.endswith(".tpp")]
    sources = [
        f for f in files if f.endswith(".cpp") and not f.endswith("unittest.cpp")
    ]
    tests = [f for f in files if f.endswith("unittest.cpp")]

    units = []
    for h in headers:
        template = None
        source = None
        test = None

        split = re.split("[./]", re.split("include/phansar/", h)[1])
        for t in templates:
            if (
                "{prefix}/detail/{suffix}.tpp".format(
                    prefix="/".join(split[:-2]), suffix="/".join(split[2:-1])
                )
                in t
            ):
                template = t
        for s in sources:
            if "{prefix}.cpp".format(prefix="/".join(split[:-1])) in s:
                source = s
        for x in tests:
            if "{prefix}.unittest.cpp".format(prefix="/".join(split[:-1])) in x:
                test = x

        units.append(Unit(header=h, template=template, source=source, test=test))

    # Units that don't have a corresponding header
    sole_units = [
        [Unit(header=h) for h in headers if all(u.header != h for u in units)],
        [Unit(template=t) for t in templates if all(u.template != t for u in units)],
        [Unit(source=s) for s in sources if all(u.source != s for u in units)],
        [Unit(test=x) for x in tests if all(u.test != x for u in units)],
    ]
    units.extend([u for su in sole_units for u in su])

    print("{} files".format(len(headers) + len(templates) + len(sources) + len(tests)))

    print("\n{} headers".format(len(headers)))
    print("{} templates".format(len(templates)))
    print("{} sources".format(len(sources)))
    print("{} tests".format(len(tests)))

    print("\n{} units".format(len(units)))

    score = 0
    for u in units:
        score += get_unit_score(u)

    percentage = score / len(units) * (100 / 5)

    if percentage >= int(arguments["--threshold"]):
        print("\npassed analysis with {}%".format(round(percentage, 2)))
        sys.exit(0)
    else:
        print("\nfailed analysis with {}%".format(round(percentage, 2)))
        sys.exit(1)
