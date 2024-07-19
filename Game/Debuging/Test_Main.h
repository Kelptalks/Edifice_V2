//
// Created by Spencer on 4/26/2024.
//

#ifndef ENGINE_TEST_MAIN_H
#define ENGINE_TEST_MAIN_H

void reportBug(const char* format, ...);

void reportTikBug(const char* format, ...);

void reportFrameBug(const char* format, ...);

void reportWorldBug(const char* format, ...);

void clearBugReports();

void clearFrameBugReports();
void clearTikBugReports();

#endif //ENGINE_TEST_MAIN_H
