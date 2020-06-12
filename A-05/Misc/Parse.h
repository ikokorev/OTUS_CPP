#pragma once

/* 
 * @brief Parsing functions library.
 */
class FParse
{
public:
    // /*
    //  * @brief Searches for Match symbols in Stream sybmols.
    //  * @param[in] Stream Symbols stream to look for Match in
    //  * @param[in] Match Symbols to look for in Stream symbols
    //  * @param[out] OutValue Out parameter to store value in, if successfully founded a match
    //  * @return True if managed to found Match in Stream, false otherwise.
    //  */
    // static bool Value(const char* Stream, const char* Match, char& OutValue);

    /*
     * @brief Sees if Stream contains give command. Returns command value, if it does.
     * @param[in] Stream Symbols stream to look for CommandName in
     * @param[in] CommandName Command name to look for in Stream symbols
     * @param[out] OutValue Out parameter to store command value in, if successfully founded it in stream
     * @return True if managed to found CommandName in Stream, false otherwise.
     */
	static bool Command(const char* Stream, const char* CommandName, char& OutValue) { return true; };
};