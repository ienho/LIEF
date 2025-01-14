/* Copyright 2017 - 2021 R. Thomas
 * Copyright 2017 - 2021 Quarkslab
 * Copyright 2017 - 2021, NVIDIA CORPORATION. All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef LIEF_ELF_BUIDLER_H_
#define LIEF_ELF_BUIDLER_H_

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

#include "LIEF/visibility.h"
#include "LIEF/iostream.hpp"

#include "LIEF/ELF/enums.hpp"

struct Profiler;

namespace LIEF {
namespace ELF {
class Binary;
class Header;
class Note;
class DynamicEntryArray;
class DynamicEntry;
class Section;

//! @brief Class which take a ELF::Binary object and reconstruct a valid binary
class LIEF_API Builder {
  public:
  friend struct ::Profiler;
  Builder(Binary *binary);

  Builder() = delete;
  ~Builder();

  void build();

  Builder& empties_gnuhash(bool flag = true);

  const std::vector<uint8_t>& get_build();
  void write(const std::string& filename) const;

  protected:
  template<typename ELF_T>
  void build();

  template<typename ELF_T>
  void build(const Header& header);

  template<typename ELF_T>
  void build_sections();

  template<typename ELF_T>
  void build_segments();

  template<typename ELF_T>
  void build_static_symbols();

  template<typename ELF_T>
  void build_dynamic();

  template<typename ELF_T>
  void build_dynamic_section();

  template<typename ELF_T>
  void build_dynamic_symbols();

  template<typename ELF_T>
  void build_dynamic_relocations();

  template<typename ELF_T>
  void build_pltgot_relocations();

  template<typename ELF_T>
  void build_section_relocations();

  template<typename ELF_T>
  void build_hash_table();

  template<typename ELF_T>
  void build_symbol_hash();

  template<typename ELF_T>
  void build_symbol_gnuhash(uint32_t new_symndx);

  uint32_t sort_dynamic_symbols();

  void build_empty_symbol_gnuhash();

  template<typename ELF_T>
  void build_symbol_requirement();

  template<typename ELF_T>
  void build_symbol_definition();

  template<typename T, typename HANDLER>
  std::vector<std::string> optimize(const HANDLER& e,
                                    std::function<std::string(const typename HANDLER::value_type)> getter,
                                    std::unordered_map<std::string, size_t> *of_map_p=nullptr);

  template<typename ELF_T>
  void build_symbol_version();

  template<typename ELF_T>
  void build_interpreter();

  template<typename ELF_T>
  void build_notes();

  void build(NOTE_TYPES type);

  size_t note_offset(const Note& note);

  bool empties_gnuhash_;

  template<typename ELF_T>
  void relocate_dynamic_array(DynamicEntryArray& entry_array, DynamicEntry& entry_size);

  template<typename ELF_T>
  void build_overlay();

  bool should_swap() const;

  Section& array_section(uint64_t addr);

  mutable vector_iostream ios_;
  Binary* binary_{nullptr};
};

} // namespace ELF
} // namespace LIEF




#endif
