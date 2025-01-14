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
#ifndef LIEF_MACHO_BINDING_INFO_COMMAND_H_
#define LIEF_MACHO_BINDING_INFO_COMMAND_H_
#include <iostream>

#include "LIEF/visibility.h"
#include "LIEF/types.hpp"
#include "LIEF/Object.hpp"

#include "LIEF/MachO/enums.hpp"


namespace LIEF {
namespace MachO {
class DylibCommand;
class SegmentCommand;
class Symbol;
class BinaryParser;

class LIEF_API BindingInfo : public Object {

  friend class BinaryParser;

  public:
    BindingInfo();
    BindingInfo(BINDING_CLASS cls, BIND_TYPES type,
        uint64_t address,
        int64_t addend = 0,
        int32_t oridnal = 0,
        bool is_weak = false,
        bool is_non_weak_definition = false, uint64_t offset = 0);

    BindingInfo& operator=(BindingInfo other);
    BindingInfo(const BindingInfo& other);
    void swap(BindingInfo& other);

    //! @brief Check if a @link MachO::SegmentCommand segment@endlink is associated with the BindingInfo
    bool has_segment() const;

    //! @brief @link MachO::SegmentCommand Segment @endlink associated with the BindingInfo
    const SegmentCommand& segment() const;
    SegmentCommand&       segment();

    //! @brief Check if a @link MachO::DylibCommand library@endlink is tied with the BindingInfo
    bool has_library() const;

    //! @brief @link MachO::DylibCommand Library@endlink associated with the BindingInfo
    const DylibCommand& library() const;
    DylibCommand&       library();

    //! @brief Check if a @link MachO::Symbol symbol@endlink is associated with the BindingInfo
    bool has_symbol() const;

    //! @brief @link MachO::Symbol Symbol @endlink associated with the BindingInfo
    const Symbol& symbol() const;
    Symbol&       symbol();

    //! @brief Address of the binding
    uint64_t address() const;
    void address(uint64_t addr);

    //! @brief Class of the binding (weak, lazy, ...)
    BINDING_CLASS binding_class() const;
    void binding_class(BINDING_CLASS bind_class);

    //! @brief Type of the binding. Most of the times it's BIND_TYPES::BIND_TYPE_POINTER
    BIND_TYPES binding_type() const;
    void binding_type(BIND_TYPES type);

    int32_t library_ordinal() const;
    void library_ordinal(int32_t ordinal);

    //! @brief Value added to the segment's virtual address when binding
    int64_t addend() const;
    void addend(int64_t addend);

    bool is_weak_import() const;
    void set_weak_import(bool val = true);

    inline bool is_non_weak_definition() const {
      return this->is_non_weak_definition_;
    }

    inline void set_non_weak_definition(bool val) {
      this->is_non_weak_definition_ = val;
    }

    //! Original relative offset of the binding opcodes
    uint64_t original_offset() const;

    virtual ~BindingInfo();

    bool operator==(const BindingInfo& rhs) const;
    bool operator!=(const BindingInfo& rhs) const;

    virtual void accept(Visitor& visitor) const override;

    LIEF_API friend std::ostream& operator<<(std::ostream& os, const BindingInfo& binding_info);

  private:
    BINDING_CLASS   class_; // STANDARD, WEAK, LAZY
    BIND_TYPES      binding_type_;
    SegmentCommand* segment_{nullptr};
    Symbol*         symbol_{nullptr};
    int32_t         library_ordinal_;
    int64_t         addend_;
    bool            is_weak_import_;
    bool            is_non_weak_definition_;
    DylibCommand*   library_{nullptr};
    uint64_t        address_{0};
    uint64_t        offset_{0};


};

}
}
#endif
