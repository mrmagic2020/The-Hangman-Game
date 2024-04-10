//
//  db.h
//  The Hangman Game
//
//  Created by Arnold Zhou on 10/4/2024.
//

#ifndef db_h
#define db_h

namespace db {
const string homeDir = getenv("HOME");
const string dir = "/.thehangmangame";
const string wbasePath = dir + "/wbase.txt";
const string configPath = dir + "/config.txt";
}

#endif /* db_h */
