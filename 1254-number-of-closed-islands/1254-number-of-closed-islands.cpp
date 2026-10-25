class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();

        auto floodFill = [&](int r, int c) {
            if (grid[r][c] != 0) return;

            stack<pair<int, int>> st;
            st.push({r, c});
            grid[r][c] = 1;

            int dr[] = {1, -1, 0, 0};
            int dc[] = {0, 0, 1, -1};

            while (!st.empty()) {
                auto [x, y] = st.top();
                st.pop();

                for (int d = 0; d < 4; ++d) {
                    int nx = x + dr[d], ny = y + dc[d];

                    if (nx >= 0 && nx < rows &&
                        ny >= 0 && ny < cols &&
                        grid[nx][ny] == 0) {
                        grid[nx][ny] = 1;
                        st.push({nx, ny});
                    }
                }
            }
        };

        // Remove all land connected to the boundary.
        for (int r = 0; r < rows; ++r) {
            floodFill(r, 0);
            floodFill(r, cols - 1);
        }

        for (int c = 0; c < cols; ++c) {
            floodFill(0, c);
            floodFill(rows - 1, c);
        }

        // Count the remaining islands.
        int count = 0;
        for (int r = 1; r < rows - 1; ++r) {
            for (int c = 1; c < cols - 1; ++c) {
                if (grid[r][c] == 0) {
                    ++count;
                    floodFill(r, c);
                }
            }
        }

        return count;
    }
};