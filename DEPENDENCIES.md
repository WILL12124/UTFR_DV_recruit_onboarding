# Dependencies

You need three things: Git, a C++17 compiler, and CMake. No third-party libraries.

---

## Linux (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install git build-essential cmake
```

`build-essential` brings GCC and Make. That's all you need.

---

## macOS

**1. Install Homebrew** (if you don't have it):
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

**2. Install dependencies:**
```bash
brew install git cmake
```

The compiler comes from Xcode Command Line Tools. Homebrew will prompt you to install them automatically if they're missing, or you can install manually:
```bash
xcode-select --install
```

---

## Windows

Install the following (in order):

1. **Git** — https://git-scm.com/download/win  
   During setup, select *"Git from the Command Line and also from 3rd-party software"*.

2. **CMake** — https://cmake.org/download/  
   Download the `.msi` installer. During setup, select *"Add CMake to the system PATH"*.

3. **MinGW-w64 (GCC for Windows)** — https://www.mingw-w64.org/downloads/  
   Recommended: install via [MSYS2](https://www.msys2.org/):
   ```bash
   # In the MSYS2 terminal:
   pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make
   ```
   Then add `C:\msys64\ucrt64\bin` to your system PATH.

**Alternative (Visual Studio):** Install [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) with the *"Desktop development with C++"* workload — it includes MSVC, CMake, and Git integration.

---

## Clone and build

```bash
git clone <repo-url>
cd recruit_onboarding
mkdir build && cd build
cmake ..
cmake --build .
```

**On Windows with MinGW**, specify the generator explicitly:
```bash
cmake .. -G "MinGW Makefiles"
cmake --build .
```

**Run the tests:**
```bash
# Linux / macOS
./run_tests

# Windows
run_tests.exe
```

See [INSTRUCTIONS.md](./INSTRUCTIONS.md) for the full problem statement.
