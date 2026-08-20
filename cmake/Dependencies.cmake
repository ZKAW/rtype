# Dependencies.cmake - Sets up compiler-specific flags and installs required tools

# Ensure Chocolatey is installed on Windows
if(WIN32)
    execute_process(COMMAND powershell -Command "Get-Package -Name Chocolatey -ErrorAction SilentlyContinue" OUTPUT_VARIABLE CHOCO_INSTALLED)
    if(NOT CHOCO_INSTALLED)
        message(STATUS "Installing Chocolatey...")
        execute_process(COMMAND powershell -Command "Set-ExecutionPolicy Bypass -Scope Process; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iwr https://chocolatey.org/install.ps1 -UseBasicParsing | iex" -Verb RunAs -Wait ERROR_QUIET)
    endif()
endif()

set(WIN_PACKAGES "")
set(DNF_PACKAGES "")
set(APT_PACKAGES "")

function(queue_package_if_missing WIN_NAME DNF_NAME APT_NAME)
    if(WIN32)
        execute_process(COMMAND powershell -Command "Get-Package -Name ${WIN_NAME} -ErrorAction SilentlyContinue" OUTPUT_VARIABLE PACKAGE_INSTALLED)
        if(NOT PACKAGE_INSTALLED)
            list(APPEND WIN_PACKAGES "${WIN_NAME}")
            set(WIN_PACKAGES "${WIN_PACKAGES}" PARENT_SCOPE)
        endif()
        return()
    endif()

    if(UNIX)

        execute_process(COMMAND which apt RESULT_VARIABLE APT_EXISTS OUTPUT_QUIET ERROR_QUIET)
        execute_process(COMMAND dpkg -s ${APT_NAME} RESULT_VARIABLE APT_INSTALLED OUTPUT_QUIET ERROR_QUIET)
        if(APT_INSTALLED EQUAL 0)
            message(STATUS "${APT_NAME} is already installed, skipping")
            return()
        endif()

        if(APT_EXISTS EQUAL 0)
            list(APPEND APT_PACKAGES "${APT_NAME}")
            set(APT_PACKAGES "${APT_PACKAGES}" PARENT_SCOPE)
            return()
        endif()

        execute_process(COMMAND which dnf RESULT_VARIABLE DNF_EXISTS OUTPUT_QUIET ERROR_QUIET)
        execute_process(COMMAND dnf list installed ${DNF_NAME} RESULT_VARIABLE DNF_INSTALLED OUTPUT_QUIET ERROR_QUIET)
        if(DNF_INSTALLED EQUAL 0)
            message(STATUS "${DNF_NAME} is already installed, skipping")
            return()
        endif()
        if(DNF_EXISTS EQUAL 0)
            list(APPEND DNF_PACKAGES "${DNF_NAME}")
            set(DNF_PACKAGES "${DNF_PACKAGES}" PARENT_SCOPE)
            return()
        endif()

        message(FATAL_ERROR "Unsupported Linux package manager, please install ${APT_NAME} manually.")
    endif()
endfunction()

function(execute_installations)
    if(WIN32 AND WIN_PACKAGES)
        foreach(PKG IN LISTS WIN_PACKAGES)
            message(STATUS "Installing ${PKG} via Chocolatey...")
            execute_process(COMMAND powershell -Command "Start-Process choco -ArgumentList 'install -y ${PKG}' -Verb RunAs -Wait" ERROR_QUIET)
        endforeach()
    endif()

    if(DNF_PACKAGES)
        message(STATUS "Installing Fedora package(s): ${DNF_PACKAGES}")
        execute_process(COMMAND sudo dnf install -y ${DNF_PACKAGES} ERROR_QUIET)
    endif()

    if(APT_PACKAGES)
        message(STATUS "Installing Ubuntu package(s): ${APT_PACKAGES}")
        execute_process(COMMAND sudo apt install -y ${APT_PACKAGES} ERROR_QUIET)
    endif()
endfunction()

queue_package_if_missing("llvm" "clang-tools-extra" "clang-tidy")
queue_package_if_missing("ccache" "ccache" "ccache")

execute_installations()
