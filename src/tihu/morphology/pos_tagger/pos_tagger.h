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
#ifndef __TIHU__POS_TAGGER__POS_TAGGER_H
#define __TIHU__POS_TAGGER__POS_TAGGER_H

#pragma once

#include "parser.h"

class CAfxManager;
class CHashManager;

class CPOSTagger
    : public IParser
{
public:
    CPOSTagger();
    ~CPOSTagger();

    bool Load(const std::string &aff_file,
              const std::string &dic_file, const std::string &dic_key);

    void ParsText(CCorpus* corpus) override;

protected:
    bool TagCompound(CWordList &word_list, CWordList::iterator &itr);
    bool CanBeCompoundWord(const std::vector<std::string> &compound) const;
    std::string GetCompoundText(const std::vector<std::string> &compound);

    std::vector<std::string> MakeCompound(const CWordList &word_list,
                                          CWordList::const_iterator itr, int compound_count);


    bool CheckWord(const std::string &text);
    bool TagWord(CWordPtr &word, const std::string &text);
    bool Breakdown(CWordList &word_list, CWordList::iterator &itr);
    bool IsDetached(char16_t c);

private:
    CAfxManager*  AfxManager;
    CHashManager* HashManager;

};

#endif