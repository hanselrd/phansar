#!/usr/bin/env python

import argparse
import base64
import glob
import json
import logging
import os
import sys

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Compile assets",
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
    optional_parser.add_argument(
        "-o", "--out-file", help="output file", default="assets.bin"
    )

    args = parser.parse_args()

    logging.basicConfig(
        stream=sys.stdout,
        format="%(asctime)s  %(levelname)-8s  |  (%(funcName)s)  %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S.%e %z",
        level=args.log_level,
    )

    basedir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    files = [
        f
        for f in glob.glob(f"{basedir}/assets/**/*", recursive=True)
        if os.path.isfile(f)
    ]

    encoded = {}

    for f in files:
        with open(f, "rb") as file:
            f = f.split(f"{basedir}/")[1]
            logging.info(f"Compiling {f}")
            encoded[f] = base64.b64encode(file.read()).decode("ascii")

    with open(args.out_file, "w") as file:
        logging.info(f"Writing to {args.out_file}")
        json.dump(encoded, file)
