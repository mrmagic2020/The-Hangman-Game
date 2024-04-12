# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog],
and this project adheres to [Semantic Versioning].

## [Unreleased]

## [1.2.0] - 2024-04-12

### Added

- Add attempt record. Repetitive guesses will not count into total attempts.
- Add options to manipulate offline word base.
- Add `update` sub-command to download latest DMG release from GitHub repository.

  - `-c` or `--check` to check for updates.
  - `-d` or `--download` to download latest release, if any.

### Changed

- New game command has been changed to `hangman game [-o]`. `game` is a subcommand.

### Removed

- `-g/--game` flag.
- `-u/--update` flag.

### Fixed

- Offline custom game set word length bugs.
- Add word length validation.
- Fix random word length bugs.

## [1.1.0] - 2024-04-10

### Added

- You can now customize a game by choosing any word length (2~15) or radomize it!
- Enter `hangman` or `hangman -h/--help` to view options list.
- You can now enjoy the game offline! (This took me TOO LONG) Enter `hangman -g -o` to start an offline game.

### Changed

- Now you have to enter `hangman -g/--game` to start a game of hangman.
- Optimize game experience by adjusting output sequence and timings.
- Use [`CLI11` library](https://github.com/CLIUtils/CLI11) to parse input commands.
- Move `about` and `update` commands.

### Fixed

- Fixed printing blank lines when there are no strikes.

## [1.0.1] - 2024-04-09

### Added

- Added `update` command.

### Changed

- Changed GET API source for better word selections.
- Changed word lengths for different difficulties.
- Added command list after finishing a game of hangman.
- Use [json library](https://github.com/nlohmann/json) to parse API results.

### Fixed

- Fixed issues with random word length generation.

## [1.0.0] - 2024-04-08

- initial release

<!-- Links -->
[keep a changelog]: https://keepachangelog.com/en/1.0.0/
[semantic versioning]: https://semver.org/spec/v2.0.0.html

<!-- Versions -->
[unreleased]: https://github.com/mrmagic2020/The-Hangman-Game/compare/v1.0.1...HEAD
[1.2.0]: https://github.com/mrmagic2020/The-Hangman-Game/releases/v1.2.0
[1.1.0]: https://github.com/mrmagic2020/The-Hangman-Game/releases/v1.1.0
[1.0.1]: https://github.com/mrmagic2020/The-Hangman-Game/releases/v1.0.1
[1.0.0]: https://github.com/mrmagic2020/The-Hangman-Game/releases/v1.0.0
