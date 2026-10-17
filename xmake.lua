-- SPDX-License-Identifier: BSD-2-Clause
-- Copyright (c) 2026 Costume-Quest-Modding

add_rules("mode.debug", "mode.release")

set_project("Cq-Decomp")
set_arch("x86")
set_languages("c++17")

add_rules("plugin.compile_commands.autoupdate", { outputdir = ".", lsp = "clangd" })

local msvc_wine = os.getenv("MSVC_WINE")

if msvc_wine and msvc_wine ~= "" then
    local bindir = path.join(msvc_wine, "bin", "x86")
    set_toolset("cc",  path.join(bindir, "cl"))
    set_toolset("cxx", path.join(bindir, "cl"))
    set_toolset("ld",  path.join(bindir, "link"))
    set_toolset("sh",  path.join(bindir, "link"))
    set_toolset("ar",  path.join(bindir, "lib"))
else
    set_toolchains("msvc")
end

target("Cq")
    set_kind("binary")
    
    add_files("src/**.cpp")
    add_includedirs("tools/include")

    add_links("kernel32", "user32", "shell32", "gdi32")

    add_includedirs("external/steamworks_sdk_114/public")
    add_linkdirs("external/steamworks_sdk_114/redistributable_bin")
    add_links("steam_api")

    add_defines("_CRT_SECURE_NO_WARNINGS")
    add_ldflags("/SUBSYSTEM:WINDOWS", {force = true})

    after_build(function (target)
        io.writefile(path.join(target:targetdir(), "steam_appid.txt"), "115100")
        os.cp("external/steamworks_sdk_114/redistributable_bin/steam_api.dll", target:targetdir())
    end)