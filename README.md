# Costume Quest Decomp

> [!IMPORTANT]
> This project is an independent open-source effort and is **not** associated, authorised, endorsed by, or in any way officially connected with **Double Fine Productions** or **Costume Quest**.

This is a functionally matching decompilation of Costume Quest. This repository only includes source code and does not include game assets or external dependencies.

## Target
- **Platform:** Windows x86 (32-bit)
- **Version:** Steam - Build ID 81338
- **MD5 Checksum:** `6F739759617989691663F9273E72C969 Cq.exe`

## Dependencies
- **Steamworks API:** v1.14 (`extern/steamworks_sdk_114`)

## Building
```
xmake f -c -p windows -m [debug|release]
xmake run Cq
```