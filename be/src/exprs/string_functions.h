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

#ifndef DORIS_BE_SRC_QUERY_EXPRS_STRING_FUNCTIONS_H
#define DORIS_BE_SRC_QUERY_EXPRS_STRING_FUNCTIONS_H

#include <re2/re2.h>

#include <iomanip>
#include <locale>
#include <sstream>
#include <string_view>

#include "anyval_util.h"
#include "gutil/strings/numbers.h"
#include "runtime/string_search.hpp"
#include "runtime/string_value.h"

namespace doris {

class Expr;
class OpcodeRegistry;
class TupleRow;

class StringFunctions {
public:
    static void init();

    static doris_udf::StringVal substring(doris_udf::FunctionContext* context,
                                          const doris_udf::StringVal& str,
                                          const doris_udf::IntVal& pos,
                                          const doris_udf::IntVal& len);
    static doris_udf::StringVal substring(doris_udf::FunctionContext* context,
                                          const doris_udf::StringVal& str,
                                          const doris_udf::IntVal& pos);
    static doris_udf::StringVal left(doris_udf::FunctionContext* context,
                                     const doris_udf::StringVal& str, const doris_udf::IntVal& len);
    static doris_udf::StringVal right(doris_udf::FunctionContext* context,
                                      const doris_udf::StringVal& str,
                                      const doris_udf::IntVal& len);
    static doris_udf::BooleanVal starts_with(doris_udf::FunctionContext* context,
                                             const doris_udf::StringVal& str,
                                             const doris_udf::StringVal& prefix);
    static doris_udf::BooleanVal ends_with(doris_udf::FunctionContext* context,
                                           const doris_udf::StringVal& str,
                                           const doris_udf::StringVal& suffix);
    static doris_udf::BooleanVal null_or_empty(doris_udf::FunctionContext* context,
                                               const doris_udf::StringVal& str);
    static doris_udf::StringVal space(doris_udf::FunctionContext* context,
                                      const doris_udf::IntVal& len);
    static doris_udf::StringVal repeat(doris_udf::FunctionContext* context,
                                       const doris_udf::StringVal& str, const doris_udf::IntVal& n);
    static doris_udf::StringVal lpad(doris_udf::FunctionContext* context,
                                     const doris_udf::StringVal& str, const doris_udf::IntVal& len,
                                     const doris_udf::StringVal& pad);
    static doris_udf::StringVal rpad(doris_udf::FunctionContext* context,
                                     const doris_udf::StringVal& str, const doris_udf::IntVal& len,
                                     const doris_udf::StringVal& pad);
    static doris_udf::StringVal append_trailing_char_if_absent(
            doris_udf::FunctionContext* context, const doris_udf::StringVal& str,
            const doris_udf::StringVal& trailing_char);
    static doris_udf::IntVal length(doris_udf::FunctionContext* context,
                                    const doris_udf::StringVal& str);
    static doris_udf::IntVal char_utf8_length(doris_udf::FunctionContext* context,
                                              const doris_udf::StringVal& str);
    static doris_udf::StringVal lower(doris_udf::FunctionContext* context,
                                      const doris_udf::StringVal& str);
    static doris_udf::StringVal upper(doris_udf::FunctionContext* context,
                                      const doris_udf::StringVal& str);
    static doris_udf::StringVal reverse(doris_udf::FunctionContext* context,
                                        const doris_udf::StringVal& str);
    static doris_udf::StringVal trim(doris_udf::FunctionContext* context,
                                     const doris_udf::StringVal& str);
    static doris_udf::StringVal ltrim(doris_udf::FunctionContext* context,
                                      const doris_udf::StringVal& str);
    static doris_udf::StringVal rtrim(doris_udf::FunctionContext* context,
                                      const doris_udf::StringVal& str);
    static doris_udf::IntVal ascii(doris_udf::FunctionContext* context,
                                   const doris_udf::StringVal& str);
    static doris_udf::IntVal instr(doris_udf::FunctionContext* context,
                                   const doris_udf::StringVal& str, const doris_udf::StringVal&);
    static doris_udf::IntVal locate(doris_udf::FunctionContext* context,
                                    const doris_udf::StringVal& str, const doris_udf::StringVal&);
    static doris_udf::IntVal locate_pos(doris_udf::FunctionContext* context,
                                        const doris_udf::StringVal& str,
                                        const doris_udf::StringVal&, const doris_udf::IntVal&);

    static bool set_re2_options(const doris_udf::StringVal& match_parameter, std::string* error_str,
                                re2::RE2::Options* opts);

    static void regexp_prepare(doris_udf::FunctionContext*,
                               doris_udf::FunctionContext::FunctionStateScope);
    static StringVal regexp_extract(doris_udf::FunctionContext*, const doris_udf::StringVal& str,
                                    const doris_udf::StringVal& pattern,
                                    const doris_udf::BigIntVal& index);
    static StringVal regexp_replace(doris_udf::FunctionContext*, const doris_udf::StringVal& str,
                                    const doris_udf::StringVal& pattern,
                                    const doris_udf::StringVal& replace);
    static void regexp_close(doris_udf::FunctionContext*,
                             doris_udf::FunctionContext::FunctionStateScope);
#if 0
    static void RegexpMatchCountPrepare(FunctionContext* context,
                                        FunctionContext::FunctionStateScope scope);
    static IntVal RegexpMatchCount2Args(FunctionContext* context, const StringVal& str,
                                        const StringVal& pattern);
    static IntVal RegexpMatchCount4Args(FunctionContext* context, const StringVal& str,
                                        const StringVal& pattern, const IntVal& start_pos,
                                        const StringVal& match_parameter);
#endif
    static StringVal concat(doris_udf::FunctionContext*, int num_children, const StringVal* strs);
    static StringVal concat_ws(doris_udf::FunctionContext*, const doris_udf::StringVal& sep,
                               int num_children, const doris_udf::StringVal* strs);
    static IntVal find_in_set(doris_udf::FunctionContext*, const doris_udf::StringVal& str,
                              const doris_udf::StringVal& str_set);

    static void parse_url_prepare(doris_udf::FunctionContext*,
                                  doris_udf::FunctionContext::FunctionStateScope);
    static StringVal parse_url(doris_udf::FunctionContext*, const doris_udf::StringVal& url,
                               const doris_udf::StringVal& part);
    static StringVal parse_url_key(doris_udf::FunctionContext*, const doris_udf::StringVal& url,
                                   const doris_udf::StringVal& key,
                                   const doris_udf::StringVal& part);
    static void parse_url_close(doris_udf::FunctionContext*,
                                doris_udf::FunctionContext::FunctionStateScope);

    static doris_udf::StringVal money_format(doris_udf::FunctionContext* context,
                                             const doris_udf::DoubleVal& v);

    static doris_udf::StringVal money_format(doris_udf::FunctionContext* context,
                                             const doris_udf::DecimalV2Val& v);

    static doris_udf::StringVal money_format(doris_udf::FunctionContext* context,
                                             const doris_udf::BigIntVal& v);

    static doris_udf::StringVal money_format(doris_udf::FunctionContext* context,
                                             const doris_udf::LargeIntVal& v);

    template <typename T, size_t N> static StringVal do_money_format(FunctionContext* context, const T int_value,
            const int32_t frac_value = 0) {
        char local[N];
        char* p = SimpleItoaWithCommas(int_value, local, sizeof(local));
        int32_t string_val_len = local + sizeof(local) - p + 3;
        StringVal result = StringVal::create_temp_string_val(context, string_val_len);
        memcpy(result.ptr, p, string_val_len - 3);
        *(result.ptr + string_val_len - 3) = '.';
        *(result.ptr + string_val_len - 2) = '0' + (frac_value / 10);
        *(result.ptr + string_val_len - 1) = '0' + (frac_value % 10);
        return result;
    };

    static StringVal split_part(FunctionContext* context, const StringVal& content,
                                const StringVal& delimiter, const IntVal& field);

    static StringVal replace(FunctionContext* context, const StringVal& origStr,
                             const StringVal& oldStr, const StringVal& newStr);

    static doris_udf::IntVal bit_length(doris_udf::FunctionContext* context,
                                    const doris_udf::StringVal& str);
};
} // namespace doris

#endif
