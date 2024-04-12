# The-Hangman-Game

 The classic Hangman game implemented in the commandline. Made with Xcode. Currently supports `macOS`.

<pre>
 +-----+     +-----+     +-----+
 |           |    \O/    |     X
 |           |     |     |    /|\
 |           |    / \    |    / \
 |           |           |
===         ===         ===
</pre>

<div align="center">

![license](https://img.shields.io/github/license/mrmagic2020/The-Hangman-Game)
![release](https://img.shields.io/github/v/release/mrmagic2020/The-Hangman-Game)
![realease-date](https://img.shields.io/github/release-date/mrmagic2020/The-Hangman-Game)
![commits-since](https://img.shields.io/github/commits-since/mrmagic2020/The-Hangman-Game/latest)

</div>

---

## Contents

- [Features](#features)
- [How to Play](#how-to-play)
  - [Command Explanation](#command-explanation)
  - [If you cannot access Terminal](#if-you-cannot-access-terminal)
- [Technical Info](#technical-info)

## Features

The classic hangman game!

- Dynamic hangman graphics!

- Four difficulties to choose from:

  - Easy (12 strikes, word length 9~15)

  - Medium (9 strikes, word length 7~11)

  - Hard (6 strikes, word length 5~9)

  - Paranoid (4 strikes, word length 3~6)

- Online word base at [https://random-word-api.herokuapp.com/home](https://random-word-api.herokuapp.com/home) - never repeating! (well, almost)

- Create an offline word base to enjoy the game offline! (Requires internet to initialize)

- Integrated in terminal - simply enter `hangman` to play!

- Customize your game! Decide what word length you want.

- (Planned for v1.2.0) Earn achievements!

## How to Play

1. Download the latest release [here](https://github.com/mrmagic2020/The-Hangman-Game/releases/latest).

2. Open the disk image.

3. Drag the executable file `hangman` into `usr/local/bin` directory (alias provided).

4. In your terminal, enter `hangman`.

5. Enjoy!

### Command Explanation

`hangman` - root command.

`game` - sub command. Starts a game of hangman.

- `--offline` or `-o` - (optional flag) make the game offline.

`wbase` - sub command. Word base manipulation.

- `--init` or `-i` - initialize offline word base.

- `--delete` or `-d` - delete offline word base.

- `--reset` or `-r` - reset offline word base (delete & initialize).

`update` - sub command. Update your hangman game.

Start an online game: `hangman -g`

Start an offline game: `hangman -g -o`

View help: `hangman -h`

### If you cannot access Terminal

We recommend you to read [this Guide](https://github.com/mrmagic2020/Remove-Jamf-on-Mac) on Terminal alternatives / removing restrictions on your Mac.

## Technical Info

**Build Environment:** MacBook Air (M1 2020), Sonoma 14.4.1

**Xcode Version:** Version 15.3 (15E204a)

**Clang Version:** Apple clang version 15.0.0 (clang-1500.3.9.4)

**Libraries Used:**

| Name | Author | Version |
| ---- | ------ | ------- |
| [curl](https://curl.se/) | | 8.7.1 |
| [JSON for Modern C++](https://github.com/nlohmann/json/) | Niels Lohmann | 3.11.3 |
| [CLI11](https://github.com/CLIUtils/CLI11) | | 2.4.1 |

**Offline Data Path:** ./.thehangmangame/ (relative to executable, usually stored in `User/`)
