#! /usr/bin/python3

import os
from distro import id
from argparse import ArgumentParser
from tempfile import TemporaryDirectory
from subprocess import check_call

parser = ArgumentParser()
parser.add_argument('--setup-only', action='store_true')
parser.add_argument('--distro', help='(default: %(default)s)',
                    default=id())
parser.add_argument('--repo', help='(default: %(default)s)',
                    default='https://github.com/FairRootGroup/FairSoft')
parser.add_argument('-j', dest="jobs", type=int,
                    default=len(os.sched_getaffinity(0)),
                    help='Number of paralell jobs (default: %(default)s)')
parser.add_argument('branch')
parser.add_argument('install_name', nargs='?')
parser.add_argument('cmakeargs', nargs='*')


def run_command(args):
    print("+", args, flush=True)
    return check_call(args)


def main():
    args = parser.parse_args()

    if args.install_name is None:
        args.install_name = args.branch
    print(args, flush=True)

    tmpprefix=f'fairsoft-for-fairroot.{args.install_name}.'
    # tmpdir='/tmp/' + tmpprefix
    # os.mkdir(tmpdir)
    # if True:
    with TemporaryDirectory(prefix=tmpprefix) as tmpdir:
        print(tmpdir)
        os.chdir(tmpdir)
        run_command(['git', 'clone', '--branch', args.branch, args.repo])
        run_command([f'./FairSoft/legacy/setup-{args.distro}.sh'])
        if args.setup_only:
            return
        run_command([
            'cmake', '-DBUILD_METHOD=legacy',
            f'-DCMAKE_INSTALL_PREFIX=/opt/fairsoft/{args.install_name}',
            '-S', 'FairSoft', '-B', 'build',
            ] + args.cmakeargs)
        run_command(['cmake', '--build', 'build', f'-j{args.jobs}'])
        run_command(['cmake', '--install', 'build'])

if __name__ == '__main__':
    main()
