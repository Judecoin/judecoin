Judecoin daemon internationalization
====================================

The Judecoin command-line tools can be translated into various languages.

If you wish to contribute translations and need help or support, please refer to
the official Judecoin community channels.

In order to use the same translation workflow as the Judecoin GUI, the command-line
tools use Qt Linguist translation files. However, to avoid the dependencies on Qt
that this normally implies, Judecoin uses a custom loader to read those files at
runtime.

### Tools for translators

In order to create, update, or build translation files, you need to have Qt tools
installed.

For translating, you need either the **Qt Linguist GUI** ([part of Qt Creator](https://www.qt.io/download)
or a [third-party standalone version](https://github.com/lelegard/qtlinguist-installers/releases)),
or another tool that supports Qt `.ts` files, such as Transifex.

The files are XML, so they can also be edited in any plain text editor if needed.

### Creating or modifying translations

You do not need anything from Qt in order to use the final translations.

To update `.ts` files after changing source code:

```bash
./utils/translations/update-translations.sh
```

To add a new language, for example Spanish with ISO code `es`:

```bash
cp translations/jude.ts translations/jude_es.ts
```

To edit translations for Spanish:

```bash
linguist translations/jude_es.ts
```

To build translations after modifying them:

```bash
./utils/translations/build-translations.sh
```

To test a translation:

```bash
LANG=es ./build/release/bin/judecoin-wallet-cli
```

To add new translatable strings in the source code, use the `tr(string)` function
if possible.

If the code is in a class, and this class does not already have a `tr()` static
function, add one that uses a context named after what `lupdate` uses for the
context, usually the fully qualified class name, for example:

```text
cryptonote::simple_wallet
```

If you need to use `tr()` in code that is not in a class, you can use the fully
qualified version, for example `simple_wallet::tr`, matching the context you want.

Use `QT_TRANSLATE_NOOP(string)` if you want to specify a context manually.

If you are getting messages of the form:

```text
Class 'cryptonote::simple_wallet' lacks Q_OBJECT macro
```

this is expected. The `Q_OBJECT` macro is not required here.
