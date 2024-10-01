# pcre2-runner

Runs partial matching with the [PCRE2](https://github.com/PCRE2Project/pcre2) regex engine, and prints match information in [Tom's Obvious Minimal Language (TOML)](https://tomhttps://toml.io/en/l.io/en/).

## Dependencies

```bash
sudo apt install libpcre2-dev
```

## Build

```bash
make
```

## Example usage

```bash
./pcre2_runner "(a|b)*" "aba"
```
