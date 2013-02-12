#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <vector>

void clearTable(char *t, int m, int n);

int main() {
    int m = 0, n = 0;
    std::string fileName;
    char *table;
    char command;

    while (std::cin >> command) {
        if (command == 'X') {
            break;
        } else if (command == 'C') {
            clearTable(table, m, n);
        } else if (command == 'L') {
            int x, y;
            char color;
            std::cin >> x >> y >> color;

            // make sure its in the table
            // if not do nothing
            if (x > 0 && x <= m && y > 0 && y <= n) {
                // change coord to index
                x--;
                y--;

                table[y*m + x] = color;
            }
        } else if (command == 'V') {
            int x, y1, y2;
            char color;
            std::cin >> x >> y1 >> y2 >> color;

            // make sure the values are in the table
            // if not do nothing
            if (x > 0 && x <= m && y1 > 0 && y1 <= n
                    && y2 > 0 && y2 <= n) {
                // make sure y2 is less than y1
                if (y1 > y2)
                    std::swap(y1, y2);
                
                // change coord to index
                x--;
                y1--;
                y2--;

                for (int i = y1; i <= y2; ++i) {
                    table[m*i + x] = color;
                }
            }
        } else if (command == 'H') {
            int x1, x2, y;
            char color;
            std::cin >> x1 >> x2 >> y >> color;

            // make sure its in the table
            // if not do nothing
            if (x1 > 0 && x1 <= m && x2 > 0 && x2 <= m
                    && y > 0 && y <= n) {
                //make sure x2 is less than x1
                if (x1 > x2)
                    std::swap(x1, x2);

                // change coord to index
                x1--;
                x2--;
                y--;

                for (int i = x1; i <= x2; ++i) {
                    table[m*y + i] = color;
                }
            }
        } else if (command == 'K') {
            int x1, x2, y1, y2;
            char color;
            std::cin >> x1 >> y1 >> x2 >> y2 >> color;

            // make sure its in the table
            // if not do nothing
            if (x1 > 0 && x1 <= m && x2 > 0 && x2 <= m
                    && y1 > 0 && y1 <= n && y2 > 0 && y2 <= n) {
                // change coord to index
                x1--; x2--;
                y1--; y2--;

                for (int i = x1; i <= x2; ++i) {
                    for (int j = y1; j <= y2; ++j) {
                        table[m*j + i] = color;
                    }
                }
            }
        } else if (command == 'F') {
            int x, y;
            char fillColor, originalColor;
            std::cin >> x >> y >> fillColor;

            // make sure its in the table
            // if not do nothing
            if (x > 0 && x <= m && y > 0 && y <= n) {
                // change coord to index
                x--;
                y--;
                originalColor = table[y*m + x];

                // do BFS to fill
                std::set<int> candidate;
                std::set<int> examined;

                candidate.insert(y*m + x);

                while (!candidate.empty()) {
                    int current = *candidate.begin();
                    candidate.erase(current);

                    int x1, y1;
                    x1 = current % m;
                    y1 = current / m;

                    // add to examined
                    examined.insert(current);

                    // can we fill this pixel
                    // if so, lets fill, then add new candidates
                    if (table[current] == originalColor) {
                        table[current] = fillColor;

                        // check for candidates, make sure they have
                        // not already been examined
                        if ((x1-1) >= 0) {
                            if (examined.count(y1*m + (x1-1)) == 0) {
                                candidate.insert(y1*m + (x1-1));
                            }
                        }
                        if ((x1+1) < m) {
                            if (examined.count(y1*m + (x1+1)) == 0) {
                                candidate.insert(y1*m + (x1+1));
                            }
                        }
                        if ((y1-1) >= 0) {
                            if (examined.count((y1-1)*m + x1) == 0) {
                                candidate.insert((y1-1)*m + x1);
                            }
                        }
                        if ((y1+1) < n) {
                            if (examined.count((y1+1)*m + x1) == 0) {
                                candidate.insert((y1+1)*m + x1);
                            }
                        }
                    }
                }
            }
        } else if (command == 'S') {
            std::cin >> fileName;
            std::cout << fileName << std::endl;

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    std::cout << table[i*m + j];
                }
                std::cout << "\n";
            }
        } else if (command == 'I') {
            std::cin >> m >> n;
            table = new char[m*n];
            clearTable(table, m, n);
        } else {
            char garbage[256];
            std::cin.getline(garbage, 256);
        }
    }

    delete table;

    return 0;
}

void clearTable(char *t, int m, int n) {
    for (int i = 0; i < m*n; ++i) {
        t[i] = 'O';
    }
}
