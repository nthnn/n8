/*
 * Copyright (c) 2024 - Nathanne Isip
 * This file is part of Zhivo.
 * 
 * Zhivo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 * 
 * Zhivo is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Zhivo. If not, see <https://www.gnu.org/licenses/>.
 */

#include "zhvlib/Reflect.hpp"

#include <zhivo/ast/TerminativeSignal.hpp>
#include <zhivo/parser/Tokenizer.hpp>

ZHIVO_FUNC(reflect_get) {
    if(args.size() != 1)
        throw TerminativeThrowSignal(
            std::move(address),
            "Expecting 1 argument, got " +
                std::to_string(args.size())
        );

    DynamicObject name = args.at(0);
    const std::string symName = name.toString();

    return symtab.getSymbol(
        std::move(address),
        symName
    );
}

ZHIVO_FUNC(reflect_has) {
    if(args.size() != 1)
        throw TerminativeThrowSignal(
            std::move(address),
            "Expecting 1 argument, got " +
                std::to_string(args.size())
        );

    DynamicObject name = args.at(0);
    const std::string symName = name.toString();

    return DynamicObject(symtab.hasSymbol(symName));
}

ZHIVO_FUNC(reflect_type) {
    if(args.size() != 1)
        throw TerminativeThrowSignal(
            std::move(address),
            "Expecting 1 argument, got " +
                std::to_string(args.size())
        );

    DynamicObject name = args.at(0);
    const std::string symName = name.toString();

    return symtab.getSymbol(
        std::move(address),
        symName
    ).objectType();
}

ZHIVO_FUNC(reflect_declare) {
    if(args.size() != 2)
        throw TerminativeThrowSignal(
            std::move(address),
            "Expecting 2 argument, got " +
                std::to_string(args.size())
        );

    DynamicObject name = args.at(0),
        value = args.at(1);

    std::string symName = name.toString();
    if(Tokenizer::isValidIdentifier(symName))
        throw TerminativeThrowSignal(
            std::move(address),
            "Invalid identifier string: " +
                symName
        );

    symtab.setSymbol(symName, value);
    return value;
}

ZHIVO_FUNC(reflect_delete) {
    if(args.size() != 1)
        throw TerminativeThrowSignal(
            std::move(address),
            "Expecting 1 argument, got " +
                std::to_string(args.size())
        );

    DynamicObject name = args.at(0);
    symtab.removeSymbol(name.toString());

    return DynamicObject();
}

ZHIVO_FUNC(reflect_invoke) {
    if(args.size() != 2)
        throw TerminativeThrowSignal(
            std::move(address),
            "Expecting 2 argument, got " +
                std::to_string(args.size())
        );

    DynamicObject name = args.at(0),
        params = args.at(1);

    if(!params.isArray())
        throw TerminativeThrowSignal(
            std::move(address),
            "Parameters must be of array type"
        );

    const std::string symName = name.toString();
    DynamicObject callable = symtab.getSymbol(
        std::move(address),
        symName
    );

    return callable.callFromNative(
        std::move(address),
        symtab,
        *params.getArray()
    );
}
