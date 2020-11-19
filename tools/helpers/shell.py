import logging
import shutil
import subprocess
import time
import typing


def shell(
    cmd: str,
    stdout: bool = True,
    stderr: bool = True,
    dryrun: bool = False,
) -> typing.Tuple[int, typing.Optional[str], typing.Optional[str]]:
    if dryrun:
        logging.info(f"(DRYRUN) cmd=`{repr(cmd)}`")
        return 0, None, None
    else:
        logging.info(f"cmd=`{repr(cmd)}`")
        process = subprocess.Popen(
            cmd,
            universal_newlines=True,
            shell=True,
            stdout=subprocess.PIPE if stdout else None,
            stderr=subprocess.PIPE if stderr else None,
        )
        if stdout:
            start = time.time()
            while True:
                try:
                    stdout, stderr = process.communicate(timeout=1)
                    break
                except subprocess.TimeoutExpired:
                    elapsed = int(time.time() - start)
                    if elapsed >= 1:
                        columns, _ = shutil.get_terminal_size()
                        progress = "=" * (elapsed % ((columns // 2) - 15))
                        print(
                            f"<{progress} {elapsed}s {progress}>".center(columns),
                            end="\r",
                            flush=True,
                        )
                    continue
        else:
            stdout, stderr = process.communicate()
        if stdout:
            logging.info(f"  stdout=`{repr(stdout)}`")
        if stderr:
            logging.info(f"  stderr=`{repr(stderr)}`")
        return (
            process.returncode,
            stdout.strip() if stdout else None,
            stderr.strip() if stderr else None,
        )
