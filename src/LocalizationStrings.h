//
//  LocalizationStrings.h
//  TP3
//
//  Created by Nathan Giraldeau on 2013-12-06.
//  Copyright (c) 2013 Nathan Giraldeau. All rights reserved.
//

#ifndef __TP3__LocalizationStrings__
#define __TP3__LocalizationStrings__

#include <iostream>
#include <map>
#include <string>
#include <fstream>

namespace beat {
    class LocalizationString {
    public:
        LocalizationString();
        ~LocalizationString();
        
        bool loadFromFile(std::string const& filepath);
        
        std::string get(std::string const& stringName, std::string const& language);
        void set(std::string const& stringName, std::string const& language, std::string const& value);
        
    private:
        std::map<std::string, std::map<std::string, std::string> > _localizedString;
    };
}
#endif
