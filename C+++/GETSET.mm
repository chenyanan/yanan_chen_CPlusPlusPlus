//
//  GETSET.cpp
//  C+++
//
//  Created by chenyanan on 2017/1/4.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#include "GETSET.hpp"
#import <UIKit/UIKit.h>
#include <iostream>

static STR tp2InPm(STR type) {
    
    STR str;
    
    if (type == "STR") {
        str = "\"\"";
    } else if (type == "INT") {
        str = "0";
    } else if (type == "PTR") {
        str = "nullptr";
    } else if (type == "Vblk") {
        str = "NULL";
    } else {
        str = "error";
    }
    
    return str;
}

static void Arr2Str(STR& strRef, VSTR& arrRef) {
    for (auto i : arrRef) {
        strRef.append(i);
    }
    strRef.append("\n");
}

static STR makeBlank(STR clsName) {
    return STR(clsName.size() * 2 + 3, ' ');
}

static STR fstLtrUpp(STR str) {
    return STR(1, toupper(str[0])) + str.substr(1, str.size());
}

static void writeHpp(STR path, STR author, STR clsName, VSTR headers, VSTR value, VSTR type, STR refCntCls) {

    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy/MM/dd"];
    NSDateFormatter *yearFormatter = [[NSDateFormatter alloc] init];
    [yearFormatter setDateFormat:@"yyyy"];
    NSString *dateNSString = [dateFormatter stringFromDate:[NSDate date]];
    NSString *yearNSString = [yearFormatter stringFromDate:[NSDate date]];

    STR year([yearNSString UTF8String]);
    STR date([dateNSString UTF8String]);
    STR pjtName([[[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleExecutableKey] UTF8String]);
    
    clsName = fstLtrUpp(clsName);

    std::string str;

    str.append("//\n");
    str.append("//  " + clsName + ".hpp\n");
    str.append("//  " + pjtName + "\n");
    str.append("//\n");
    str.append("//  Created By " + author + " on " + date + "\n");
    str.append("//  Copyright © " + year + "年 " + author + ". All rights reserved.\n");
    str.append("//\n\n");

    str.append("#ifndef " + clsName + "_hpp\n");
    str.append("#define " + clsName + "_hpp\n\n");
    str.append("#include \"TYPE.h\"\n");
    
    if (refCntCls.length() > 0) {
        str.append("#include \"" + refCntCls + ".h\"\n");
    }
    
    str.append("\nstruct " + clsName);
    
    if (refCntCls.length() > 0) {
        str.append(" : public " + refCntCls);
    }
    
    str.append(" {\n");
    
    str.append("public:\n");

    VSTR getArray, setArray, valueArray;

    auto length = value.size();
    
    for (auto i = 0; i < length; ++i) {
        if (value[i].front() == '_') {
            value[i].erase(0,1);
        }
    }
    
    for (auto i = 0; i < length; ++i) {
        getArray.emplace_back("\tconst " + type[i] + "& get" + fstLtrUpp(value[i]) + "();\n");
        setArray.emplace_back("\tvoid set" + fstLtrUpp(value[i]) + "(" + type[i] + " " + value[i] + ");\n");
        valueArray.emplace_back("\tmutable " + type[i] + " _" + value[i] + ";\n");
    }

    Arr2Str(str, valueArray);
    Arr2Str(str, getArray);
    Arr2Str(str, setArray);

    str.append("\t~" + clsName + "() {}\n");
    str.append("\t" + clsName + "(");

    for (auto i = 0; i < length; ++i) {
        str.append(type[i] + " " + value[i] + " = " + tp2InPm(type[i]) + ",");
    }
    str.pop_back();
    str.append(");\n");
    
    str.append("};\n");
    
    str.append("\ntemplate<typename T> class SPR;\n");
    str.append("typedef SPR<" + clsName + "> S" + clsName + ";\n");
    str.append("typedef std::vector<SPR<" + clsName + ">> VS" + clsName + ";\n\n");

    str.append("\n#endif /* " + clsName + "_hpp */");

    std:: cout << str << std::endl;

    NSString *string = [NSString stringWithCString:str.c_str() encoding:4];
    [string writeToFile:[NSString stringWithCString:(path + "/" + clsName + ".hpp").c_str() encoding:4] atomically:YES encoding:4 error:nil];
}

static void writeCpp(STR path, STR author, STR clsName, VSTR headers, VSTR value, VSTR type, STR refCntCls) {

    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy/MM/dd"];
    NSDateFormatter *yearFormatter = [[NSDateFormatter alloc] init];
    [yearFormatter setDateFormat:@"yyyy"];
    NSString *dateNSString = [dateFormatter stringFromDate:[NSDate date]];
    NSString *yearNSString = [yearFormatter stringFromDate:[NSDate date]];

    STR year([yearNSString UTF8String]);
    STR date([dateNSString UTF8String]);
    STR pjtName([[[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleExecutableKey] UTF8String]);
    
    clsName = fstLtrUpp(clsName);

    std::string str;

    str.append("//\n");
    str.append("//  " + clsName + ".cpp\n");
    str.append("//  " + pjtName + "\n");
    str.append("//\n");
    str.append("//  Created By " + author + " on " + date + "\n");
    str.append("//  Copyright © " + year + "年 " + author + ". All rights reserved.\n");
    str.append("//\n\n");

    str.append("#include \"" + clsName + ".hpp\"\n");

    VSTR getterArray, setterArray, defInitArray, paraInitArray, deinitArray;

    getterArray.emplace_back("#pragma mark - getter\n");
    
    auto length = value.size();
    
    for (auto i = 0; i < length; ++i) {
        if (value[i].front() == '_') {
            value[i].erase(0,1);
        }
    }
    
    for (auto i = 0; i <length; ++i) {
        getterArray.emplace_back("const " + type[i] + "& " + clsName + "::get" + fstLtrUpp(value[i]) + "() {\n");
        getterArray.emplace_back("\treturn _" + value[i] + ";\n");
        getterArray.emplace_back("}\n\n");
    }

    setterArray.emplace_back("#pragma mark - setter\n");
    for (auto i = 0; i < length; ++i) {
        setterArray.emplace_back("void " + clsName + "::set" + fstLtrUpp(value[i]) + "(" + type[i] + " " + value[i] + ") {\n");
        setterArray.emplace_back("\t_" + value[i] + " = " + value[i] + ";\n}\n\n");
    }

    paraInitArray.emplace_back("#pragma mark - parameter init\n");
    paraInitArray.emplace_back(clsName + "::" + clsName + "(" + type[0] + " " + value[0] + ",\n");
    for (auto i = 1; i < length; ++i) {
        paraInitArray.emplace_back(makeBlank(clsName) + type[i] + " " + value[i] + ",\n");
    }
    paraInitArray[paraInitArray.size() - 1][paraInitArray[paraInitArray.size() - 1].length() - 2] = ')';
    paraInitArray.emplace_back(":\n");
    if (refCntCls.length() > 0) {
        paraInitArray.emplace_back(refCntCls + "(1),\n");
    }
    for (auto i = 0; i < length; ++i) {
        paraInitArray.emplace_back("_" + value[i] + "(" + value[i] + "),\n");
    }

    paraInitArray[paraInitArray.size() - 1][paraInitArray[paraInitArray.size() - 1].length() - 2] = ' ';
    paraInitArray.emplace_back("{\n\n}\n\n");

    deinitArray.emplace_back("#pragma mark - deinit\n");
    deinitArray.emplace_back(clsName + "::~" + clsName + "() {\n" + "\tprintf(\"" + clsName + " dealloc\\n\");\n}\n");

    Arr2Str(str, getterArray);
    Arr2Str(str, setterArray);
    Arr2Str(str, paraInitArray);
    Arr2Str(str, deinitArray);

    std::cout << str << std::endl;

    NSString *string = [NSString stringWithCString:str.c_str() encoding:4];
    [string writeToFile:[NSString stringWithCString:(path + "/" + clsName + ".mm").c_str() encoding:4] atomically:YES encoding:4 error:nil];
}

void GETSET::make(STR path, STR author, STR clsName, VSTR headers, VSTR value, VSTR type, STR refCntCls) {
    writeHpp(path, author, clsName, headers, value, type, refCntCls);
    writeCpp(path, author, clsName, headers, value, type, refCntCls);
}
