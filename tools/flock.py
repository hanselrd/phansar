#!/usr/bin/env python3

"""
Manage file locks when executing shell commands
"""

from utility.shell import shell
import argparse
import logging
import os
import sys
import filelock

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
        add_help=False,
    )

    positional_parser = parser.add_argument_group("positional arguments")
    positional_parser.add_argument(
        "TARGET", help="target to lock, can be a file or directory"
    )

    # required_parser = parser.add_argument_group("required arguments")

    optional_parser = parser.add_argument_group("optional arguments")
    optional_parser.add_argument(
        "-h",
        "--help",
        help="show this help message and exit",
        action="help",
        default=argparse.SUPPRESS,
    )
    optional_parser_group1 = optional_parser.add_mutually_exclusive_group()
    optional_parser_group1.add_argument(
        "--directory", help="assume target is a directory", action="store_true"
    )
    optional_parser_group1.add_argument(
        "--file", help="assume target is a file", action="store_true"
    )
    optional_parser.add_argument(
        "-c", "--command", help="command to execute", action="append", nargs="+"
    )
    optional_parser_group2 = optional_parser.add_mutually_exclusive_group()
    optional_parser_group2.add_argument(
        "-n", "--nonblock", help="fail rather than wait", action="store_true"
    )
    optional_parser_group2.add_argument(
        "-w",
        "--timeout",
        help="wait for a limited amount of time (secs)",
        type=float,
        default=-1,
    )

    args = parser.parse_args()

    logging.basicConfig(
        format="%(asctime)s  %(levelname)-8s  |  (%(funcName)s)  %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S.%e %z",
        level=logging.DEBUG,
        handlers=[logging.StreamHandler(sys.stdout)],
    )

    if not args.directory and not args.file:
        if os.path.isdir(args.TARGET):
            os.makedirs(args.TARGET, exist_ok=True)
            lock_file = f"{args.TARGET}/LOCK"
        else:
            lock_file = f"{args.TARGET}.lock"
    elif args.directory:
        os.makedirs(args.TARGET, exist_ok=True)
        lock_file = f"{args.TARGET}/LOCK"
    elif args.file:
        lock_file = f"{args.TARGET}.lock"

    with filelock.FileLock(lock_file, args.timeout if not args.nonblock else 0) as lock:
        for c in args.command:
            shell(" ".join(c))
