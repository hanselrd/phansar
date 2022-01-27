#!/usr/bin/env python

from utility.shell import shell
import argparse
import glob
import logging
import os
import re
import sys
import tempfile

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Update vendor libraries",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
        add_help=False,
    )

    # positional_parser = parser.add_argument_group("positional arguments")

    # required_parser = parser.add_argument_group("required arguments")

    optional_parser = parser.add_argument_group("optional arguments")
    optional_parser.add_argument(
        "-h",
        "--help",
        help="show this help message and exit",
        action="help",
        default=argparse.SUPPRESS,
    )
    optional_parser.add_argument(
        "-l",
        "--log-level",
        help="set logging level",
        choices=[
            logging.NOTSET,
            logging.DEBUG,
            logging.INFO,
            logging.WARNING,
            logging.ERROR,
            logging.CRITICAL,
        ],
        default=logging.DEBUG,
    )

    args = parser.parse_args()

    logging.basicConfig(
        stream=sys.stdout,
        format="%(asctime)s  %(levelname)-8s  |  (%(funcName)s)  %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S.%e %z",
        level=args.log_level,
    )

    os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

    files = [
        f
        for f in glob.glob("vendor/*/CMakeLists.txt", recursive=True)
        if os.path.isfile(f)
    ]

    for f in files:
        with tempfile.TemporaryDirectory() as tmpdir:
            with open(f, "r") as file:
                data = file.read()
                groups = re.search(
                    "GITHUB_REPOSITORY\s*(\S*)\s*#\s*(\S*)\s*GIT_TAG\s*([^\s\)]*)",
                    data,
                ).groups()
                shell(
                    f"git clone https://github.com/{groups[0]}.git -b {groups[1]} {tmpdir}"
                )
                shell(f"cd {tmpdir} && git checkout {groups[2]}")
                _, stdout, _ = shell(f"cd {tmpdir} && git rev-parse HEAD")
                HEAD_HASH = stdout.split("\n")[0]
                _, stdout, _ = shell(f"cd {tmpdir} && git rev-parse origin/{groups[1]}")
                ORIGIN_HASH = stdout.split("\n")[0]

            if HEAD_HASH != ORIGIN_HASH:
                data = data.replace(groups[2], ORIGIN_HASH)

                with open(f, "w") as file:
                    file.write(data)
