////
////  makemodel.cpp
////  C++Project
////
////  Created by chenyanan on 2017/1/3.
////  Copyright © 2017年 chenyanan. All rights reserved.
////
//
//#include "makemodel.hpp"
//#import <UIKit/UIKit.h>
//#include <iostream>
//
//STR tp2PmTp(STR type) {
//    
//    STR str;
//    
//    if (type == "CUStr") {
//        str = "STR";
//    } else if (type == "CUInt") {
//        str = "CInt";
//    } else if (type == "CUImg") {
//        str = "CImg";
//    } else if (type == "CUVbk") {
//        str = "CVBlk";
//    } else {
//        str = "error";
//    }
//    
//    return str;
//}
//
//
//STR tp2Pm(STR type) {
//    
//    STR str;
//    
//    if (type == "CUStr") {
//        str = "str";
//    } else if (type == "CUInt") {
//        str = "integer";
//    } else if (type == "CUImg") {
//        str = "img";
//    } else if (type == "CUVbk") {
//        str = "blk";
//    }else {
//        str = "error";
//    }
//    
//    return str;
//}
//
//STR tp2BkPmTp(STR type) {
//    
//    STR str;
//    
//    if (type == "CUStr") {
//        str = "CSBlk";
//    } else if (type == "CUInt") {
//        str = "CIBlk";
//    } else if (type == "CUImg") {
//        str = "CMBlk";
//    } else if (type == "CUVbk") {
//        str = "CVBlk";
//    } else {
//        str = "error";
//    }
//    
//    return str;
//}
//
//STR tp2BkTp(STR type) {
//    
//    STR str;
//    
//    if (type == "CUStr") {
//        str = "CUSbk";
//    } else if (type == "CUInt") {
//        str = "CUIbk";
//    } else if (type == "CUImg") {
//        str = "CUMbk";
//    } else if (type == "CUVbk") {
//        str = "CUVbk";
//    } else {
//        str = "error";
//    }
//    
//    return str;
//}
//
//STR tp2BkAt(STR type) {
//    STR str;
//    
//    if (type == "CUStr") {
//        str = "str";
//    } else if (type == "CUInt") {
//        str = "integer";
//    } else if (type == "CUImg") {
//        str = "img";
//    } else if (type == "CUVbk") {
//        str = "";
//    } else {
//        str = "error";
//    }
//    
//    return str;
//}
//
//STR tp2InPm(STR type) {
//    
//    STR str;
//    
//    if (type == "CUStr") {
//        str = "nullptr";
//    } else if (type == "CUInt") {
//        str = "0";
//    } else if (type == "CUImg") {
//        str = "nullptr";
//    } else if (type == "CUVbk") {
//        str = "nil";
//    } else {
//        str = "error";
//    }
//    
//    return str;
//}
//
//void Arr2Str(STR& strRef, VSTR& arrRef) {
//    for (auto i : arrRef) {
//        strRef.append(i);
//    }
//    strRef.append("\n");
//}
//
//STR makeBlank(STR clsName) {
//    return STR(clsName.size() * 2 + 3, ' ');
//}
//
//STR fstLtrUpp(STR str) {
//    return STR(1, toupper(str[0])) + str.substr(1, str.size());
//}
//
//STR fstLtrLow(STR str) {
//    return STR(1, tolower(str[0])) + str.substr(1, str.size());
//}
//
//void writeHpp(STR path, STR author, STR clsName, VSTR headers, VSTR value, VSTR type, bool isRefCnt) {
//    
//    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
//    [dateFormatter setDateFormat:@"yyyy/MM/dd"];
//    NSDateFormatter *yearFormatter = [[NSDateFormatter alloc] init];
//    [yearFormatter setDateFormat:@"yyyy"];
//    NSString *dateNSString = [dateFormatter stringFromDate:[NSDate date]];
//    NSString *yearNSString = [yearFormatter stringFromDate:[NSDate date]];
//    
//    STR year([yearNSString UTF8String]);
//    STR date([dateNSString UTF8String]);
//    STR pjtName([[[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleExecutableKey] UTF8String]);
//    
//    std::string str;
//    
//    str.append("//\n");
//    str.append("//  " + clsName + ".hpp\n");
//    str.append("//  " + pjtName + "\n");
//    str.append("//\n");
//    str.append("//  Created By " + author + " on " + date + "\n");
//    str.append("//  Copyright © " + year + "年 " + author + ". All rights reserved.\n");
//    str.append("//\n\n");
//    
//    str.append("#ifndef " + clsName + "_hpp\n");
//    str.append("#define " + clsName + "_hpp\n\n");
//    str.append("#include \"CType.h\"\n\n");
//    str.append("class " + clsName + " {\n\n");
//    str.append("\tfriend void swap(" + clsName + "& lhs, " + clsName + "& rhs);\n\n");
//    str.append("public:\n");
//    
//    VSTR getArray, setNoTrgArray, setArray, setWlStArray, setDiStArray, valueArray, WlStArray, DiStArray;
//    
//    auto length = value.size();
//    for (auto index = 0; index < length; ++index) {
//        getArray.emplace_back("\tconst " + type[index] + "& get" + fstLtrUpp(value[index]) + "();\n");
//        setNoTrgArray.emplace_back("\tvoid set" + fstLtrUpp(value[index]) + "NoTrg(" + tp2PmTp(type[index]) + " " + tp2Pm(type[index]) + ");\n");
//        setArray.emplace_back("\tvoid set" + fstLtrUpp(value[index]) + "(" + tp2PmTp(type[index]) + " " + tp2Pm(type[index]) + ");\n");
//        setWlStArray.emplace_back("\tvoid setWlSt" + fstLtrUpp(value[index]) + "Blk(" + tp2BkPmTp(type[index]) + " blk);\n");
//        setDiStArray.emplace_back("\tvoid setDiSt" + fstLtrUpp(value[index]) + "Blk(" + tp2BkPmTp(type[index]) + " blk);\n");
//        valueArray.emplace_back("\t" + type[index] + " _" + value[index] + ";\n");
//        WlStArray.emplace_back("\t" + tp2BkTp(type[index]) + " _" + value[index] + "WlStBlk;\n");
//        DiStArray.emplace_back("\t" + tp2BkTp(type[index]) + " _" + value[index] + "DiStBlk;\n");
//    }
//    
//    Arr2Str(str, getArray);
//    Arr2Str(str, setNoTrgArray);
//    Arr2Str(str, setArray);
//    Arr2Str(str, setWlStArray);
//    Arr2Str(str, setDiStArray);
//    
//    str.append("\n");
//    
//    str.append("\t" + clsName + "();\n");
//    str.append("\t~" + clsName + "();\n");
//    str.append("\t" + clsName + "(");
//    
//    for (auto index = 0; index < length; ++index) {
//        str.append(tp2PmTp(type[index]) + " " + value[index] + ",");
//    }
//    str.pop_back();
//    str.append(");\n\n");
//    
//    str.append("\t" + clsName + "(" + clsName + "&& " + fstLtrLow(clsName) + ") = delete;\n");
//    str.append("\t" + clsName + "(const " + clsName + "& " + fstLtrLow(clsName) + ") = delete;\n");
//    str.append("\t" + clsName + "& operator=(" + clsName + " " + fstLtrLow(clsName) + ") = delete;\n");
//    
//    str.append("\nprivate:\n");
//    
//    Arr2Str(str, valueArray);
//    Arr2Str(str, WlStArray);
//    Arr2Str(str, DiStArray);
//    
//    str.append("};\n");
//    
//    str.append("\n#endif /* " + clsName + "_hpp */");
//    
//    std:: cout << str << std::endl;
//    
////    NSString *string = [NSString stringWithCString:str.c_str() encoding:4];
////    [string writeToFile:[NSString stringWithCString:(path + "/" + clsName + ".hpp").c_str() encoding:4] atomically:YES encoding:4 error:nil];
//}
//
//void writeCpp(STR path, STR author, STR clsName, VSTR headers, VSTR value, VSTR type, bool isRefCnt) {
//
//    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
//    [dateFormatter setDateFormat:@"yyyy/MM/dd"];
//    NSDateFormatter *yearFormatter = [[NSDateFormatter alloc] init];
//    [yearFormatter setDateFormat:@"yyyy"];
//    NSString *dateNSString = [dateFormatter stringFromDate:[NSDate date]];
//    NSString *yearNSString = [yearFormatter stringFromDate:[NSDate date]];
//    
//    STR year([yearNSString UTF8String]);
//    STR date([dateNSString UTF8String]);
//    STR pjtName([[[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleExecutableKey] UTF8String]);
//    
//    std::string str;
//    
//    str.append("//\n");
//    str.append("//  " + clsName + ".cpp\n");
//    str.append("//  " + pjtName + "\n");
//    str.append("//\n");
//    str.append("//  Created By " + author + " on " + date + "\n");
//    str.append("//  Copyright © " + year + "年 " + author + ". All rights reserved.\n");
//    str.append("//\n\n");
//    
//    str.append("#include \"" + clsName + ".hpp\"\n");
//    str.append("#import <Foundation/Foundation.h>\n\n");
//    
//    VSTR swapArray, getterArray, setterArray, setNoTrgArray, setWlStArray, setDiStArray, defInitArray, paraInitArray, deinitArray;
//    
//    swapArray.emplace_back("#pragma mark - swap\n");
//    swapArray.emplace_back("void swap(" + clsName + "& lhs, " + clsName + "& rhs) {\n");
//    swapArray.emplace_back("\tusing std::swap;\n");
//    for (auto i : value) {
//        swapArray.emplace_back("\tswap(lhs._" + i + ", rhs._" + i + ");\n");
//    }
//    swapArray.emplace_back("}\n");
//    swapArray.emplace_back("\n");
//    
//    getterArray.emplace_back("#pragma mark - getter\n");
//    auto length = value.size();
//    for (auto index = 0; index <length; ++index) {
//        getterArray.emplace_back("const " + type[index] + "& " + clsName + "::get" + fstLtrUpp(value[index]) + "() {\n");
//        getterArray.emplace_back("\treturn _" + value[index] + ";\n");
//        getterArray.emplace_back("}\n\n");
//    }
//    
//    setterArray.emplace_back("#pragma mark - setter\n");
//    for (auto index = 0; index < length; ++index) {
//        setterArray.emplace_back("void " + clsName + "::set" + fstLtrUpp(value[index]) + "(" + tp2PmTp(type[index]) + " " + tp2Pm(type[index]) + ") {\n");
//        setterArray.emplace_back("\tif (*_" + value[index] + "WlStBlk) {\n");
//        setterArray.emplace_back("\t\t(*_" + value[index] + "WlStBlk)(" + tp2BkAt(type[index]) + ");\n\t}\n\n");
//        setterArray.emplace_back("\tset" + fstLtrUpp(value[index]) + "NoTrg(" + tp2Pm(type[index]) + ");\n\n");
//        setterArray.emplace_back("\tif (*_" + value[index] + "DiStBlk) {\n");
//        setterArray.emplace_back("\t\t(*_" + value[index] + "DiStBlk)(" + tp2BkAt(type[index]) + ");\n\t}\n}\n\n");
//    }
//    
//    for (auto index = 0; index < length; ++index) {
//        setNoTrgArray.emplace_back("void " + clsName + "::set" + fstLtrUpp(value[index]) + "NoTrg(" + tp2PmTp(type[index]) + " " + tp2Pm(type[index]) + ") {\n");
//        setNoTrgArray.emplace_back("\t_" + value[index] + ".reset(new " + tp2PmTp(type[index]) + "(" + tp2Pm(type[index]) + "));\n}\n\n");
//    }
//    
//    for (auto index = 0; index < length; ++index) {
//        setWlStArray.emplace_back("void " + clsName + "::setWlSt" + fstLtrUpp(value[index]) + "Blk(" + tp2BkPmTp(type[index]) + " blk) {\n");
//        setWlStArray.emplace_back("\t_" + value[index] + "WlStBlk.reset(new " + tp2BkPmTp(type[index]) + "(blk));\n}\n\n");
//    }
//    
//    for (auto index = 0; index < length; ++index) {
//        setDiStArray.emplace_back("void " + clsName + "::setDiSt" + fstLtrUpp(value[index]) + "Blk(" + tp2BkPmTp(type[index]) + " blk) {\n");
//        setDiStArray.emplace_back("\t_" + value[index] + "DiStBlk.reset(new " + tp2BkPmTp(type[index]) + "(blk));\n}\n\n");
//    }
//    
//    defInitArray.emplace_back("#pragma mark - default init\n");
//    defInitArray.emplace_back(clsName + "::" + clsName + "()\n:\n");
//    for (auto index = 0; index < length; ++index) {
//        defInitArray.emplace_back("_" + value[index] + "(new " + tp2PmTp(type[index]) + "(" + tp2InPm(type[index]) + ")),\n");
//    }
//    for (auto index = 0; index < length; ++index) {
//        defInitArray.emplace_back("_" + value[index] + "WlStBlk(new " + tp2BkPmTp(type[index]) + "(nil)),\n");
//    }
//    for (auto index = 0; index < length; ++index) {
//        defInitArray.emplace_back("_" + value[index] + "DiStBlk(new " + tp2BkPmTp(type[index]) + "(nil)),\n");
//    }
//    defInitArray[defInitArray.size() - 1][defInitArray[defInitArray.size() - 1].length() - 2] = ' ';
//    defInitArray.emplace_back("{\n\n}\n\n");
//    
//    paraInitArray.emplace_back("#pragma mark - parameter init\n");
//    paraInitArray.emplace_back(clsName + "::" + clsName + "(" + tp2PmTp(type[0]) + " " + value[0] + ",\n");
//    for (auto index = 1; index < length; ++index) {
//        paraInitArray.emplace_back(makeBlank(clsName) + tp2PmTp(type[index]) + " " + value[index] + ",\n");
//    }
//    paraInitArray[paraInitArray.size() - 1][paraInitArray[paraInitArray.size() - 1].length() - 2] = ')';
//    paraInitArray.emplace_back(":\n");
//    for (auto index = 0; index < length; ++index) {
//        paraInitArray.emplace_back("_" + value[index] + "(new " + tp2PmTp(type[index]) + "(" + value[index] + ")),\n");
//    }
//    for (auto index = 0; index < length; ++index) {
//        paraInitArray.emplace_back("_" + value[index] + "WlStBlk(new " + tp2BkPmTp(type[index]) + "(nil)),\n");
//    }
//    for (auto index = 0; index < length; ++index) {
//        paraInitArray.emplace_back("_" + value[index] + "DiStBlk(new " + tp2BkPmTp(type[index]) + "(nil)),\n");
//    }
//    paraInitArray[paraInitArray.size() - 1][paraInitArray[paraInitArray.size() - 1].length() - 2] = ' ';
//    paraInitArray.emplace_back("{\n\n}\n\n");
//    
//    deinitArray.emplace_back("#pragma mark - deinit\n");
//    deinitArray.emplace_back(clsName + "::~" + clsName + "() {\n" + "\tNSLog(@\"" + clsName + " dealloc\");\n}\n");
//    
//    Arr2Str(str, swapArray);
//    Arr2Str(str, getterArray);
//    Arr2Str(str, setterArray);
//    Arr2Str(str, setNoTrgArray);
//    Arr2Str(str, setWlStArray);
//    Arr2Str(str, setDiStArray);
//    Arr2Str(str, defInitArray);
//    Arr2Str(str, paraInitArray);
//    Arr2Str(str, deinitArray);
//    
//    std::cout << str << std::endl;
//    
////    NSString *string = [NSString stringWithCString:str.c_str() encoding:4];
////    [string writeToFile:[NSString stringWithCString:(path + "/" + clsName + ".mm").c_str() encoding:4] atomically:YES encoding:4 error:nil];
//}
//
//void makemodel::make(STR path, STR author, STR clsName, VSTR headers, VSTR value, VSTR type, STR refCntCls) {
//    writeHpp(path, author, clsName, headers, value, type, isRefCnt);
//    writeCpp(path, author, clsName, headers, value, type, isRefCnt);
//}
