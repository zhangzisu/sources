#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
int n, m;
inline bool isVowel(char c) { return c == 'a' || c == 'o' || c == 'y' || c == 'i' || c == 'e'; }
inline bool isConsonant(char c) { return !isVowel(c); }
inline bool isMark(char c) { return c == '.' || c == '!' || c == '?'; }
const std::vector<std::string> se_prefix = {"s", "hs", "hc", "x", "o"};
std::map<std::string, int> nouns, auxiliaries;
std::set<std::string> verbs;
std::vector<std::string> tokens;
inline bool startsWith(const std::string &s, const std::string &p) { return s.compare(0, p.size(), p) == 0; }
std::string goPlural(std::string noun) {
	for (const auto &prefix : se_prefix) {
		if (startsWith(noun, prefix)) {
			return "se" + noun;
		}
	}
	if (startsWith(noun, "f")) return "sev" + noun.substr(1);
	if (startsWith(noun, "ef")) return "sev" + noun.substr(2);
	if ((int)noun.length() >= 2 && noun[0] == 'y' && isConsonant(noun[1])) return "sei" + noun.substr(1);
	return "s" + noun;
}
std::vector<std::string> split(const std::string &str) {
	std::vector<std::string> ret;
	bool dirty = true;
	for (int i = 0; i < (int)str.length(); i++) {
		if (isMark(str[i])) {
			ret.push_back(std::string() + str[i]);
			dirty = true;
		} else {
			if (dirty) {
				dirty = false;
				ret.push_back(std::string() + str[i]);
			} else {
				ret.back().push_back(str[i]);
			}
		}
	}
	return ret;
}
int main() {
	nouns["i"] |= 1 << 0;
	nouns["eh"] |= 1 << 0;
	nouns["ehs"] |= 1 << 0;
	nouns["ti"] |= 1 << 0;
	nouns["uoy"] |= 1 << 1;
	nouns["yeht"] |= 1 << 1;
	nouns["ew"] |= 1 << 1;

	auxiliaries["ma"] |= 1 << 0;
	auxiliaries["si"] |= 1 << 0;
	auxiliaries["saw"] |= 1 << 0;
	auxiliaries["lliw"] |= 1 << 0;
	auxiliaries["llahs"] |= 1 << 0;

	auxiliaries["era"] |= 1 << 1;
	auxiliaries["erew"] |= 1 << 1;
	auxiliaries["lliw"] |= 1 << 1;

	// freopen("language.in", "r", stdin);
	// freopen("language.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin >> n >> m;
	std::string token;
	for (int i = 1; i <= n; i++) {
		std::cin >> token;
		nouns[token] |= 1 << 0;
		nouns[goPlural(token)] |= 1 << 1;
	}
	for (int i = 1; i <= m; i++) {
		std::cin >> token;
		verbs.insert(token);
	}
	while (std::cin >> token) {
		const auto splitted = split(token);
		for (const auto &token : splitted) {
			if (isMark(token.back())) {
				// if ((int)token.length() > 1) {
				// 	tokens.push_back(token.substr(0, token.length() - 1));
				// }
				if (tokens.size() >= 3U && tokens.size() <= 4U) {
					if (token.back() == '?') std::swap(tokens[0], tokens[1]);
					if (nouns.count(tokens[0]) && auxiliaries.count(tokens[1])) {
						if (nouns[tokens[0]] & auxiliaries[tokens[1]]) {
							if (tokens.size() == 3U) {
								puts(verbs.count(tokens[2]) ? "Yes" : "No");
							} else {
								puts(tokens[2] == "oy" && verbs.count(tokens[3]) ? "Yes" : "No");
							}
						} else {
							puts("No");
						}
					} else {
						puts("No");
					}
				} else {
					puts("No");
				}
				tokens.clear();
			} else {
				tokens.push_back(token);
			}
		}
	}
}