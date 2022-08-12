# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/esp/esp-idf/components/bootloader/subproject"
  "C:/GIT/sistema_automacao_hidroponia/sistema_de_automacao_hidroponia/build/bootloader"
  "C:/GIT/sistema_automacao_hidroponia/sistema_de_automacao_hidroponia/build/bootloader-prefix"
  "C:/GIT/sistema_automacao_hidroponia/sistema_de_automacao_hidroponia/build/bootloader-prefix/tmp"
  "C:/GIT/sistema_automacao_hidroponia/sistema_de_automacao_hidroponia/build/bootloader-prefix/src/bootloader-stamp"
  "C:/GIT/sistema_automacao_hidroponia/sistema_de_automacao_hidroponia/build/bootloader-prefix/src"
  "C:/GIT/sistema_automacao_hidroponia/sistema_de_automacao_hidroponia/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/GIT/sistema_automacao_hidroponia/sistema_de_automacao_hidroponia/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
