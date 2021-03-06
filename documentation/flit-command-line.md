# FLiT Command-Line

FLiT comes with a command-line tool called `flit`.  This command-line tool is
simply a symbolic link to `flit.py`.  In the repository, it is located in
`scripts/flitcli/flit.py`.  When installed, it is installed in
`<PREFIX>/share/flit/scripts/flit.py`.

This command is split up into many subcommands.  Most of it is self documented.
Simply call

```bash
flit --help
```

for more information.

Possible subcommands:

* [flit help](#flit-help): display help for a specific subcommand
* [flit init](#flit-init): Initializes a flit test directory for use
* [flit update](#flit-update): Updates the Makefile based on `flit-config.toml`
* [flit check](#flit-check): Verifies the correctness of a config file
* [flit run](#flit-run): Run flit on the configured remote machine(s)
* [flit analyze](#flit-analyze): Runs analysis on a previous flit run

## flit help

This can display the help documentation for a specific subcommand.  This is
just a convenience subcommand.

```bash
flit help init
```

is identical to

```bash
flit init --help
```

This is the preferred method for getting the latest documentation for the
`flit` command-line tool.  The documentation within the tool is more likely to
be up to date than this markdown description.

## flit init

Initializes a flit test directory for use. It will initialize the directory by
copying the default configuration file into the given directory. If a
configuration file already exists, this command does nothing. The config file
is called `flit-config.toml`.

To see how to modify `flit-config.toml`, see the documentation for [FLiT
Configuration File](flit-configuration-file.md).

There are a few other files copied over:

* `flit-config.toml`: the configuration file
* `custom.mk`: a custom file that is included at the end of Makefile
* `Makefile`: an autogenerated Makefile using `flit-config.toml`
* `main.cpp`: a minimal main function.  No modification necessary, but you may
  if you want.
* `tests/Empty.cpp`: This is a template for how to write tests in this
  framework

If you want to play with the litmus tests in this directory, you can pass the
`--litmus-tests` which will copy over the litmus tests into the `tests`
directory for use.

## flit update

Updates the `Makefile` based on `flit-config.toml`. The `Makefile` is
autogenerated and should not be modified manually. If there are things you want
to replace or add, you can use `custom.mk` which is included at the end of the
`Makefile`.  So, you may add rules, add to variables, or override variables.

You do not actually need to call this explicitly since the `Makefile` will
automatically call `flit update` to update itself if `flit-config.toml` has
changed.  You should only call it directly if you want to manually examine the
autogenerated `Makefile`.

## flit check

_not yet implemented_

This command only verifies the correctness of the configurations you have for
your flit tests. As part of this verification, this command checks to see if
the remote connections are capable of being done, such as the connection to
the machines to run the software, the connection to the database machine, and
the connection to the database machine from the run machine. You may need to
provide a few SSH passwords to do this check.

Since this subcommand is not yet implemented, it may change in nature when it
does finally get implemented.

## flit run

_not yet implemented_

Run flit on the configured remote machine(s). Note that you may need to
provide a password for SSH, but that should be taken care of pretty early on
in the process. The results should be sent to the database computer for later
analysis.

## flit analyze

_not yet implemented_

Runs analysis on a previous flit run. The analysis will be of the current flit
repository and will create a directory called analysis inside of the flit
directory.

