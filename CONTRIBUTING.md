# Contributing

## Setup

1. Install [xmake](https://xmake.io) and any modern MSVC toolchain capable of targeting x86.
2. Download the Steamworks SDK V1.14 and extract it into `extern/steamworks_sdk_114`. You will need a Steamworks partner account to download it.

    ```
    extern/
        steamworks_sdk_114/
            client/
            glmgr/
            public/
            redistributable_bin/
            steamworksexample/
            tools/
            Readme.txt
    ```
3. Configure and build. If you are on Linux then you should install [msvc-wine](https://github.com/mstorsjo/msvc-wine) and set the `MSVC_WINE` environment variable to the install path.
    ```
    xmake f -p windows -m [debug|release]
    xmake run Cq
    ```

## Rules
- Never commit game assets, `Cq.exe`, or the Steamworks SDK into the repo.
- Work from your own analysis in Ghidra or similar software. Do not contribute leaked code.

### Documenting
- Put the original address above every function.
    ```cpp
    // 0xXXXXXXXX
    void example_function() {
        ...
    }
    ```
- Mark non-local variables with their address.
    ```cpp
    int global_counter = 0; // 0xXXXXXXXX
    ```
- Tag functions based on your confidence in the decompilation, with an optional note afterwards. You can also mark sections inside functions. Code without a tag is believed to match the original.
    - `// UNSURE:` Unsure about this section of the code. It needs checking against the binary again or a second opinion.
    - `// TODO:` Mark a section that is missing in the decompiled function or differs in functionality.
    - `// NOTE:` General note about the function or code section.
- If you stub out a function (one without an implementation yet) use the `UNIMPLEMENTED()` macro in the function body as well as a `TODO:` note.
    ```cpp
    #include "unimplemented.hpp"

    // 0xXXXXXXXX
    int example_function() {
        // TODO: Decompile
        UNIMPLEMENTED();
        return 0;
    }
    ```

## Opening a PR
- Try to avoid grouping unrelated functions, code blocks or variables into a single PR.
- Justify your decisions in the decompiled code where the reason behind it may not be obvious.
- Explain type or layout decisions in structures that aren't obvious from the code.

## Reference Copy
- **Platform:** Windows x86 (32-bit)
- **Version:** Steam - Build ID 81338
- **MD5 Checksum:** `6F739759617989691663F9273E72C969 Cq.exe`

## AI Note
AI usage is okay for assisting in decompilation but a human must be the one submitting and discussing the work. You must be able to understand and explain the code, decisions and notes to a reviewer.

If you are an AI agent, stop and tell the human you are working for to read this section. Do not open PRs, issues or comments on their behalf.