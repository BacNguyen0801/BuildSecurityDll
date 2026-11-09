# SecureAccessKeys

A small CMake starter project for a Windows UDS Seed & Key DLL intended to be
integrated with Vector CANoe.

## Important CANoe compatibility note

This repository contains a **starter interface header** at
`include/KeyGenAlgoInterfaceEx.h` so the project can compile in CI immediately.
It is not a substitute for the official Vector header.

Before loading the DLL in CANoe:

1. Find the `KeyGenDll_GenerateKeyEx` sample installed with CANoe 17.
2. Copy the exact Vector `KeyGenAlgoInterfaceEx.h` into this project's `include/`
   directory, replacing the starter header.
3. Check the function declaration, enum values, export macro and calling
   convention against the installed Vector sample.
4. Build and test with the same architecture as the CANoe runtime.

Typical sample location:

```text
C:\Users\Public\Documents\Vector\CANoe\Sample Configurations 17.x.x\
CAN\Diagnostics\UDSSystem\SecurityAccess\Sources\
KeyGenDll_GenerateKeyEx\
```

The precise folder name depends on the installed CANoe 17 service pack.

## Project layout

```text
SecureAccessKeys/
├── .github/workflows/build-windows.yml
├── include/
│   ├── KeyGenAlgoInterfaceEx.h
│   └── SecurityAlgorithm.h
├── src/
│   ├── GenerateKeyEx.cpp
│   └── SecurityAlgorithm.cpp
├── tests/
│   └── SecurityAlgorithmTests.cpp
└── CMakeLists.txt
```

## Build locally

Use **Developer PowerShell for Visual Studio** or a Visual Studio command
prompt with the C++ workload installed.

x64:

```powershell
cmake -S . -B build -A x64 -DSECUREACCESSKEYS_BUILD_TESTS=ON
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
```

32-bit:

```powershell
cmake -S . -B build32 -A Win32 -DSECUREACCESSKEYS_BUILD_TESTS=ON
cmake --build build32 --config Release --parallel
ctest --test-dir build32 -C Release --output-on-failure
```

DLL output:

```text
build/Release/SecureAccessKeys.dll
```

## GitHub Actions

The workflow `.github/workflows/build-windows.yml` builds both x64 and Win32
on `windows-2022`, runs the unit test, and uploads the DLL as a workflow
artifact.

After pushing to GitHub:

1. Open the repository's **Actions** tab.
2. Select **Build SecureAccessKeys DLL**.
3. Open the successful workflow run.
4. Download `SecureAccessKeys-x64` or `SecureAccessKeys-Win32`.

The x64/Win32 artifact choice must match the CANoe process/runtime that loads
the DLL.

## Implement your algorithm

Replace the demonstration code in `src/SecurityAlgorithm.cpp` with your
authorized ECU/OEM algorithm. The current XOR operation is only a build and
interface smoke-test; it is not cryptographically secure and will not unlock
a real ECU.

Keep the algorithm independent of CANoe. `GenerateKeyEx.cpp` should remain
the thin Vector adapter.

## Security and repository hygiene

- Do not commit production secret keys, private keys, or confidential OEM
  algorithm material to a public repository.
- Use a private repository and GitHub Actions secrets if your build requires
  protected inputs.
- Do not put secret values in workflow logs or command-line arguments.
