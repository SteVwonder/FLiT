'Implements the update subcommand'

import argparse
import os
import sys
import toml

import flitconfig as conf
import flitutil

brief_description = 'Updates the Makefile based on flit-config.toml'

def main(arguments, prog=sys.argv[0]):
    parser = argparse.ArgumentParser(
            prog=prog,
            description='''
                Updates the Makefile based on flit-config.toml.  The Makefile
                is autogenerated and should not be modified manually.  If there
                are things you want to replace or add, you can use custom.mk
                which is included at the end of the Makefile.  So, you may add
                rules, add to variables, or override variables.
                ''',
            )
    parser.add_argument('-C', '--directory', default='.',
                        help='The directory to initialize')
    args = parser.parse_args(arguments)

    projconf = toml.load(os.path.join(args.directory, 'flit-config.toml'))
    print('Updating {0}'.format(os.path.join(args.directory, 'Makefile')))
    flitutil.process_in_file(
        os.path.join(conf.data_dir, 'Makefile.in'),
        os.path.join(args.directory, 'Makefile'),
        {
            'compiler': os.path.realpath(projconf['hosts'][0]['compilers'][0]['binary']),
            'flit_include_dir': conf.include_dir,
            'flit_lib_dir': conf.lib_dir,
            'flit_script': os.path.join(conf.script_dir, 'flit.py'),
        },
        overwrite=True)

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
