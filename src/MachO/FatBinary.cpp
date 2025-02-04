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
#include <numeric>
#include <iomanip>

#include "LIEF/MachO/FatBinary.hpp"
#include "LIEF/MachO/Builder.hpp"
#include "LIEF/MachO/Binary.hpp"

namespace LIEF {
namespace MachO {

FatBinary::FatBinary() :
  binaries_{}
{}


FatBinary::FatBinary(const std::vector<Binary*>& binaries) :
  binaries_{binaries}
{}


size_t FatBinary::size() const {
  return this->binaries_.size();
}


it_binaries FatBinary::begin() {
  return this->binaries_;
}

it_const_binaries FatBinary::begin() const {
  return this->binaries_;
}


it_binaries FatBinary::end() {
  return it_binaries{this->binaries_}.end();
}

it_const_binaries FatBinary::end() const {
  return it_const_binaries{this->binaries_}.end();
}


Binary* FatBinary::pop_back() {
  if (this->binaries_.size() > 0) {
    Binary* last = this->binaries_.back();
    this->binaries_.pop_back();
    return last;
  }
  return nullptr;
}

Binary& FatBinary::at(size_t index) {
  return const_cast<Binary&>(static_cast<const FatBinary*>(this)->at(index));
}
const Binary& FatBinary::at(size_t index) const {
  if (index >= this->size()) {
    throw std::out_of_range("Bad index");
  }
  return *this->binaries_[index];
}


Binary& FatBinary::back() {
  return const_cast<Binary&>(static_cast<const FatBinary*>(this)->back());
}
const Binary& FatBinary::back() const {
  return *this->binaries_.back();
}

Binary& FatBinary::operator[](size_t index) {
  return const_cast<Binary&>(static_cast<const FatBinary*>(this)->operator[](index));
}

const Binary& FatBinary::operator[](size_t index) const {
  return this->at(index);
}

std::unique_ptr<Binary> FatBinary::take(CPU_TYPES cpu) {
  auto it = std::find_if(std::begin(this->binaries_), std::end(this->binaries_),
      [cpu] (const Binary* bin) {
        return bin->header().cpu_type() == cpu;
      });
  if (it == std::end(this->binaries_)) {
    return nullptr;
  }
  std::unique_ptr<Binary> ret(*it);
  this->binaries_.erase(it);
  return ret;
}
std::unique_ptr<Binary> FatBinary::take(size_t index) {
  if (index >= this->binaries_.size()) {
    return {};
  }
  auto it = this->binaries_.begin();
  std::advance(it, index);
  std::unique_ptr<Binary> ret(*it);
  this->binaries_.erase(it);
  return ret;
}

void FatBinary::write(const std::string& filename) {
  Builder::write(this, filename);
}

std::vector<uint8_t> FatBinary::raw() {
  Builder builder{this};
  return builder();
}

std::ostream& operator<<(std::ostream& os, const FatBinary& fatbinary) {
  for (const Binary& binary : fatbinary) {
    os << binary;
    os << std::endl << std::endl;
  }

  return os;
}

FatBinary::~FatBinary() {
  for (Binary* b : this->binaries_) {
    delete b;
  }
}


}
}
