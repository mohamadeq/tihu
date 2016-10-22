/*******************************************************************************
* This file is part of Tihu.
*
* Tihu is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Tihu is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Tihu.  If not, see <http://www.gnu.org/licenses/>.
*
* Contributor(s):
*    Mostafa Sedaghat Joo (mostafa.sedaghat@gmail.com)
*
*******************************************************************************/
#include "persian_to_phoneme.h"
#include "path_manager.h"

#include <algorithm>

#define LTS_LOG_WORDS


CPersianToPhoneme::CPersianToPhoneme()
{
#ifdef LTS_LOG_WORDS
    LoadWordFrequency();
#endif
}

CPersianToPhoneme::~CPersianToPhoneme()
{
#ifdef LTS_LOG_WORDS
    SaveWordFrequency();
#endif
}

bool CPersianToPhoneme::LoadModel(const std::string &model)
{
    return g2p.LoadModel(model);
}

void CPersianToPhoneme::LoadWordFrequency()
{
    std::string log_file = CPathManager::GetInstance()->GetLogFile("unknown_frquency.txt");
    
    FILE* file = fopen(log_file.c_str(), "r");

    if(!file) {
        return;
    }

    char buf[1024];
    while(fgets(buf, 1024, file)) {
        try {
            std::string word = strtok(buf, "\t");
            int freq = std::stoi(strtok(NULL, "\t"));

            WordFrequency[word] = freq;
        } catch(...) {
        }
    }

    fclose(file);
}

void CPersianToPhoneme::SaveWordFrequency()
{
    std::string log_file = CPathManager::GetInstance()->GetLogFolder();
    log_file += "unknown_word_freqeuncy.txt";

    FILE* file = fopen(log_file.c_str(), "w");

    if(!file) {
        return;
    }


    char buf[1024];
    for(auto const &i : WordFrequency) {
        std::string word = i.first;
        int freq = i.second;

        sprintf(buf, "%s\t%d\n", word.c_str(), freq);
        fwrite(buf, 1, strlen(buf), file);
    }

    fclose(file);
}

std::string CPersianToPhoneme::Convert(const std::string &word)
{
#ifdef LTS_LOG_WORDS
    ++WordFrequency[word];
#endif

    std::string pronunciation;
    
    pronunciation = g2p.Convert(word);
    
    return pronunciation;
}