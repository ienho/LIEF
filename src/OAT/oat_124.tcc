/* Copyright 2017 - 2021 R. Thomas
 * Copyright 2017 - 2021 Quarkslab
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

#include <type_traits>

#include "logging.hpp"

#include "LIEF/utils.hpp"

#include "LIEF/DEX.hpp"

#include "LIEF/OAT/EnumToString.hpp"

namespace LIEF {
namespace OAT {

template<>
void Parser::parse_dex_files<OAT124_t>() {
  using oat_header = typename OAT124_t::oat_header;

  size_t nb_dex_files = this->oat_binary_->header().nb_dex_files();

  uint64_t dexfiles_offset = sizeof(oat_header) + this->oat_binary_->header_.key_value_size();

  LIEF_DEBUG("OAT DEX file located at offset: 0x{:x}", dexfiles_offset);

  std::vector<uint32_t> classes_offsets_offset;
  classes_offsets_offset.reserve(nb_dex_files);

  this->stream_->setpos(dexfiles_offset);
  for (size_t i = 0; i < nb_dex_files; ++i ) {

    LIEF_DEBUG("Dealing with OAT DEX file #{:d}", i);

    std::unique_ptr<DexFile> dex_file{new DexFile{}};

    uint32_t location_size = this->stream_->read<uint32_t>();

    const char* loc_cstr = this->stream_->read_array<char>(location_size, /* check */false);
    std::string location;

    if (loc_cstr != nullptr) {
      location = {loc_cstr, location_size};
    }

    dex_file->location(location);

    uint32_t checksum = this->stream_->read<uint32_t>();
    dex_file->checksum(checksum);

    uint32_t dex_struct_offset = this->stream_->read<uint32_t>();
    dex_file->dex_offset(dex_struct_offset);

    uint32_t class_offsets = this->stream_->read<uint32_t>();
    classes_offsets_offset.push_back(class_offsets);

    uint32_t type_lookup_offset = this->stream_->read<uint32_t>();
    dex_file->lookup_table_offset(type_lookup_offset);

    this->oat_binary_->oat_dex_files_.push_back(dex_file.release());
  }

  if (this->has_vdex()) {
    DEX::it_dex_files dexfiles = this->vdex_file_->dex_files();
    if (dexfiles.size() != this->oat_binary_->oat_dex_files_.size()) {
      LIEF_WARN("Inconsistent number of vdex files");
      return;
    }
    for (size_t i = 0; i < dexfiles.size(); ++i) {
      DexFile* oat_dex_file = this->oat_binary_->oat_dex_files_[i];
      this->oat_binary_->dex_files_.push_back(&dexfiles[i]);
      oat_dex_file->dex_file_ = &dexfiles[i];


      const uint32_t nb_classes = dexfiles[i].header().nb_classes();

      uint32_t classes_offset = classes_offsets_offset[i];
      oat_dex_file->classes_offsets_.reserve(nb_classes);
      for (size_t cls_idx = 0; cls_idx < nb_classes; ++cls_idx) {
        uint32_t off = this->stream_->peek<uint32_t>(classes_offset + cls_idx * sizeof(uint32_t));
        oat_dex_file->classes_offsets_.push_back(off);
      }
    }
  }
}


} // Namespace OAT
} // Namespace LIEF
