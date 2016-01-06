//
//  LocalizationStrings.cpp
//  TP3
//
//  Created by Nathan Giraldeau on 2013-12-06.
//  Copyright (c) 2013 Nathan Giraldeau. All rights reserved.
//

#include "LocalizationStrings.h"

namespace beat {
    LocalizationString::LocalizationString() {
        
    }
    
    LocalizationString::~LocalizationString() {
        
    }
    
    bool LocalizationString::loadFromFile(std::string const& filepath) {
        std::ifstream stream;
        
        
        stream.open(filepath.c_str());
        
        if(!stream.is_open()) {
            std::cerr << "Impossible to load '" << filepath << "' localized strings" << std::endl;
            return false;
        }
        
        while(stream.good()) {
            // On récupère le nom de la string
            std::string stringname;
            stream >> stringname;
            
            std::string token;
            stream >> token;
            
            if(token == "{") {
                do {
                    std::string language;
                    stream >> token;
                    
                    if(token != "{" && token != "}") {
                        language = token;
                        std::string string;
                        char actual;
                        bool b = false;
                        
                        bool ok = false;
                        
                        do {
                            actual = stream.get();
                            
                            if(actual == '@' && b == false) {
                                b = true;
                            }
                            else if(actual == '@' && b == true) {
                                ok = true;
                            }
                            else {
                                string.push_back(actual);
                            }
                            
                        } while(!ok);
                        
                        this->set(stringname, language, string);
                    }
                    
                }while(token != "}");
            }
            else {
                return false;
            }
            
        }
        
        return true;
    }
    
    std::string LocalizationString::get(std::string const& stringName, std::string const& language) {
        // Ajouter un assert
        
        std::map<std::string, std::map<std::string, std::string> >::iterator it;
        if((it = _localizedString.find(stringName)) == _localizedString.end()) {
            return "???";
        }
        else {
            if((it->second).find(language) == (it->second).end()) {
                if(language != "english")
                    return "!" + get(stringName, "english");
                else
                    return "Undefined string";
            }
        }
        
        
        return _localizedString[stringName][language];
    }
    
    void LocalizationString::set(std::string const& stringName, std::string const& language, std::string const& value) {
        _localizedString[stringName][language] = value;
    }
}