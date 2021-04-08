// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include "vec/common/assert_cast.h"
#include "vec/data_types/data_type.h"
// #include <vec/DataTypes/DataTypeWithSimpleSerialization.h>

namespace doris::vectorized {

/** Implements part of the IDataType interface, common to all numbers and for Date and DateTime.
  */
template <typename T>
class DataTypeNumberBase : public IDataType {
    static_assert(IsNumber<T>);

public:
    static constexpr bool is_parametric = false;
    using FieldType = T;

    const char* getFamilyName() const override { return TypeName<T>::get(); }
    TypeIndex getTypeId() const override { return TypeId<T>::value; }

    // void serializeText(const IColumn & column, size_t row_num, WriteBuffer & ostr, const FormatSettings &) const override;
    // void deserializeText(IColumn & column, ReadBuffer & istr, const FormatSettings & settings) const override;
    // void serializeTextJSON(const IColumn & column, size_t row_num, WriteBuffer & ostr, const FormatSettings & settings) const override;
    // void deserializeTextJSON(IColumn & column, ReadBuffer & istr, const FormatSettings &) const override;
    // void deserializeTextCSV(IColumn & column, ReadBuffer & istr, const FormatSettings & settings) const override;
    Field getDefault() const override;

    /** Format is platform-dependent. */
    // void serializeBinary(const Field & field, WriteBuffer & ostr) const override;
    // void deserializeBinary(Field & field, ReadBuffer & istr) const override;
    // void serializeBinary(const IColumn & column, size_t row_num, WriteBuffer & ostr) const override;
    // void deserializeBinary(IColumn & column, ReadBuffer & istr) const override;
    // void serializeBinaryBulk(const IColumn & column, WriteBuffer & ostr, size_t offset, size_t limit) const override;
    // void deserializeBinaryBulk(IColumn & column, ReadBuffer & istr, size_t limit, double avg_value_size_hint) const override;

    // void serializeProtobuf(const IColumn & column, size_t row_num, ProtobufWriter & protobuf, size_t & value_index) const override;
    // void deserializeProtobuf(IColumn & column, ProtobufReader & protobuf, bool allow_add_row, bool & row_added) const override;

    MutableColumnPtr createColumn() const override;

    bool isParametric() const override { return false; }
    bool haveSubtypes() const override { return false; }
    bool shouldAlignRightInPrettyFormats() const override { return true; }
    bool textCanContainOnlyValidUTF8() const override { return true; }
    bool isComparable() const override { return true; }
    bool isValueRepresentedByNumber() const override { return true; }
    bool isValueRepresentedByInteger() const override;
    bool isValueRepresentedByUnsignedInteger() const override;
    bool isValueUnambiguouslyRepresentedInContiguousMemoryRegion() const override { return true; }
    bool haveMaximumSizeOfValue() const override { return true; }
    size_t getSizeOfValueInMemory() const override { return sizeof(T); }
    bool isCategorial() const override { return isValueRepresentedByInteger(); }
    bool canBeInsideLowCardinality() const override { return true; }

    void to_string(const IColumn& column, size_t row_num, BufferWritable& ostr) const;
};

} // namespace doris::vectorized
