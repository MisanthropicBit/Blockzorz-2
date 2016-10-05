#include "grid.hpp"
#include "block.hpp"
#include "audio_manager.hpp"
#include "particle_effect.hpp"
#include "game.hpp"
#include <stdio.h>
#include <iostream>

grid grid::game_grid;

grid::grid() {
    for (int r = 0; r < GRID_MAX_ROWS; ++r) {
        for (int c = 0; c < GRID_MAX_COLUMNS; ++c) {
            grid[r][c] = nullptr;
        }
    }
    
    combos               = 0;
    score                = 0;
    spawn_time           = SPAWN_RATE;
    spawn_interval       = SPAWN_INTERVAL;
    start_spawn_interval = START_SPAWN_INTERVAL;
    increased            = 0;
    game_over            = false;
    spawning             = false;
    spawntime_left       = 0;
    spawn_row            = 13;
    spawn_col            = 0;
    spawn_list.clear();
}

grid::~grid() {
    for (int r = 0; r < GRID_MAX_ROWS; ++r) {
        for (int c = 0; c < GRID_MAX_COLUMNS; ++c) {
            if (grid[r][c]) {
                delete grid[r][c];
                grid[r][c] = nullptr;
            }
        }
    }

    for (int i = 0; i < spawn_list.size(); ++i) {
        if (spawn_list[i]) {
            delete spawn_list[i];
        }
    }

    spawn_list.clear();
}

grid& grid::game_grid() {
    return grid::game_grid;
}

void grid::update(int dt) {
    if (!spawning) {
        pe_manager.update(dt);
        spawn_time -= dt;

        if (increased < MAX_INCREASES) {
            spawn_interval -= dt;

            if (spawn_interval <= 0) {
                ++increased;
                spawn_interval = SPAWN_INTERVAL;
            }
        }

        if (spawn_time <= 0) {
            spawn_block_at_top();
            spawn_time = SPAWN_RATE - increased * SPAWN_DECAY;
        }

        if (!spawn_list.empty()) {
            for (int i = 0; i < spawn_list.size(); ++i) {
                spawn_list[i]->object::update(dt);

                if (SpawnList[i]->position.y + SpawnList[i]->h >= GetRowYCoord(0)) {
                    if (grid[0][spawn_list[i]->column()]) {
                        game_over = true;
                    } else {
                        spawn_list[i]->fall();
                        grid[0][spawn_list[i]->column()] = spawn_list[i];
                        spawn_list.erase(spawn_list.begin() + i);
                    }
                }
            }
        }
    } else {
        spawn_blocks(dt);
    }

    for (int r = 0; r < GRID_MAX_ROWS; ++r) {
        for (int c = 0; c < GRID_MAX_COLUMNS; ++c) {
            if (grid[r][c]) {
                if (grid[r][c]->dead()) {
                    particle_explosion_effect* pex = new particle_explosion_effect("./images/cursor.png",
                                                                                   6,
                                                                                   0.1f,
                                                                                   0.1f,
                                                                                   get_col_x_coord(c) + grid[r][c]->w/2,
                                                                                   get_row_y_coord(r) + grid[r][c]->h/2);
                    pex->set_update_interval(40, 80);
                    pex->show();
                    pe_manager.add_effect(pex);
                    
                    delete grid[r][c];
                    grid[r][c] = nullptr;
                } else {
                    if (grid[r][c]->needs_checking()) {
                        check_block(r, c);
                    }

                    grid[r][c]->update(dt);
                }
            }
        }
    }
}

void grid::draw() {
    for (int r = 0; r < GRID_MAX_ROWS; ++r) {
        for (int c = 0; c < GRID_MAX_COLUMNS; ++c) {
            if (grid[r][c]) {
                grid[r][c]->draw();
            }
        }
    }

    if (!spawn_list.empty()) {
        for (int i = 0; i < spawn_list.size(); i++) {
            spawn_list[i]->draw();
        }
    }

    pe_manager.draw();
}

void grid::spawn() {
    combos    = 0;
    score     = 0;
    game_over = false;
    spawning  = true;
    increased = 0;
    spawn_row = 13;
    spawn_col = 0;

    debugtext.set_font_file("./fonts/biocomv2.ttf", 30);
}

void grid::despawn() {
    for (int r = 0; r < GRID_MAX_ROWS; ++r) {
        for (int c = 0; c < GRID_MAX_COLUMNS; ++c) {
            if (grid[r][c]) {
                delete grid[r][c];
                grid[r][c] = nullptr;
            }
        }
    }

    for (int i = 0; i < SpawnList.size(); ++i) {
        if (spawn_list[i]) {
            delete spawn_list[i];
        }
    }

    spawn_list.clear();
    debug_text.close();
    pe_manager.clear();
}

void grid::spawn_block_at_top() {
    int rand_col = rand() % 8;

    if (grid[0][randcol]) {
        game_over = true;
    } else {
        block* block = new Block(static_cast<block_type>(rand() % 5), 0, rand_col);
        block->position = vector(get_col_x_coord(rand_col), -BLOCK_HEIGHT);
        block->speed = vector(0, FALL_SPEED);
        spawn_list.push_back(block);
        block = nullptr;
    }
}

void grid::swap_blocks(int row, int col) {
    // If there is nothing to swap, don't bother
    if (!grid[row][col] && !grid[row][col + 1]) {
        return;
    }

    print_grid();

    block* block1 = grid[row][col];
    block* block2 = grid[row][col + 1];
    int col2 = col + 1;

    if (block1) {
        // If there is a block at the 1st position
        if (!block1->falling() && !block1->dead()) {
            // This block is neither falling or dead
            if (block2) {
                // There is a block besides this block
                if (!block2->falling() && !block2->dead()) {
                    // This block is not falling or dead, so swap
                    block1->swap_right();
                }
            } else if (!block2) {
                // If there is not a block besides it
                if (row != GRID_MAX_ROWS - 1) {
                    // If we are not at the bottom row
                    if (grid[row + 1][col2]) {
                        // If there is a block below and to the right of block1
                        if (grid[row + 1][col2]->falling() && !grid[row + 1][col2]->dead()) {
                            // If this block is falling and not dead
                            if (grid[row + 1][col2]->position.y >= get_row_y_coord(row + 1)) {
                                // The block has passed by, so swap
                                block1->swap_right();
                            }
                        } else {
                            // No block besides it, not at bottom row, block below and to the right
                            // and that block is not falling and dead
                            block1->swap_right();
                        }
                    } else {
                        // No block besides it, there is not a block below and to the right
                        block1->swap_right();
                    }
                } else {
                    // No block beside it, we are at the bottom row
                    block1->swap_right();
                }
            }
        }
    }

    print_grid();

    if (block2) {
        if (!block2->falling() && !block2->dead()) {
            if (block1) {
                if (!block1->falling() && !block1->dead()) {
                    block2->swap_left();
                }
            } else if (!block1) {
                if (row != GRID_MAX_ROWS - 1) {
                    if (grid[row + 1][col]) {
                        if (grid[row + 1][col]->falling() && !grid[row + 1][col]->dead()) {
                            if (grid[row + 1][col]->position.y >= GetRowYCoord(row + 1)) {
                                // Block has passed, so if there is no block besides it, swap it
                                block2->swap_left(); 
                            }
                        } else {
                            block2->swap_left();
                        }
                    } else {
                        block2->swap_left();
                    }
                } else {
                    block2->swap_left();
                }
            }
        }
    }

    print_grid();

    //if(block1)
    //{
    //  if(block1->IsSwapping())
    //  {
    //      grid[row][col2] = block1;
    //      grid[row][col]  = block2;
    //  }
    //}
    //else if(block2)
    //{
    //  if(block2->IsSwapping())
    //  {
    //      grid[row][col2] = block1;
    //      grid[row][col]  = block2;
    //  }
    //}

    // The following code we check to see whether or not we need to change
    // the pointers stored in the 'grid' object if the blocks are swapping.
    if (block1 && block2) {
        if (block1->swapping() && block2->swapping()) {
            grid[row][col2] = block1;
            grid[row][col]  = block2;
        }
    } else if (block1 && !block2) {
        if(block1->swapping()) {
            grid[row][col2] = block1;
            grid[row][col]  = nullptr;
        }
    } else if (!block1 && block2) {
        if (block2->swapping()) {
            grid[row][col]  = block2;
            grid[row][col2] = nullptr;
        }
    }

    // Move blocks above empty space if necessary
    if (!block1 && row != 1) {
        for (int i = row - 1; i >= 1; --i) {
            if (grid[i][col2]) {
                grid[i][col2]->Fall();
            } else {
                break;
            }
        }
    }

    if (!block2 && row != 1) {
        for (int i = row - 1; i >= 1; --i) {
            if (grid[i][col]) {
                grid[i][col]->fall();
            } else {
                break;
            }
        }
    }

    print_grid();
}

void grid::check_block(int row, int col) {
    int score = 0;

    // Is the block even valid?
    if(validate_block(row, col) == BLOCK_TYPE_NOGOOD) {
        return;
    }

    block_type type = grid[row][col]->block_type();

    int connected_above = 0;
    int connected_below = 0;
    //bool pointsAboveOrBelow = false;

    // Check above block
    for (int i = row - 1; i >= 0; --i) {
        if (validate_block(i, col) == type) {
            ++connected_above;
        } else {
            break;
        }
    }

    // Check below block
    for (int i = row + 1; i < GRID_MAX_ROWS; ++i) {
        if(ValidateBlock(i, col) == type) {
            ++connected_below;
        } else {
            break;
        }
    }

    if(connecteda_bove + connected_below >= 2) {
        //pointsAboveOrBelow = true;
        score += connected_above + connected_below;

        for (int i = row + connectedbelow; i >= row - connectedabove; --i) {
            grid[i][col]->kill();
        }

        for (int i = row - connectedabove - 1; i >= 0; --i) {
            if (validate_block(i, col) != BLOCK_TYPE_NOGOOD) {
                grid[i][col]->Fall();
            } else {
                break;
            }
        }
    }

    int connected_left  = 0;
    int connected_right = 0;

    // Check left of block
    for (int i = col - 1; i >= 0; --i) {
        if(validate_block(row, i) == type) {
            ++connectedleft;
        } else {
            break;
        }
    }

    // Check right of block
    for (int i = col + 1; i < GRID_MAX_COLUMNS; ++i) {
        if (ValidateBlock(row, i) == blocktype) {
            ++connected_right;
        } else {
            break;
        }
    }

    // We need at least three connected blocks
    if (connected_left + connected_right >= 2) {
        // Add to score
        score += connectedleft + connectedright;

        for (int i = col - connectedleft; i <= col + connectedright; ++i) {
            // Run through blocks again and kill them
            grid[row][i]->kill();
        }

        for (int i = col - connectedleft; i <= col + connectedright; ++i) {
            // Run through blocks than now need to fall
            //if(pointsAboveOrBelow && i == col) // Points scored in vertical direction, don't make 
            //  continue;

            for (int j = row - 1; j >= 1; --j) {
                if (validate_block(j, i) != BLOCK_TYPE_NOGOOD) {
                    grid[j][i]->fall();
                } else {
                    break;
                }
            }
        }
    }

    if (score > 0) {
        // If the player scored any points
        // For the block we're checking
        score += 1; 
        grid[row][col]->kill();

        if (game::game_settings.cf_mode_unlocked) {
            audio_manager::get()->play_sound("yes!", 0);
        }

        if(score > 3) {
            // More than three blocks connected counts as a combo
            ++combos;
            score *= POINTS_PER_BLOCK;
            score += COMBO_POINTS * (score - 3);
        } else {
            score *= POINTS_PER_BLOCK;
        }

        this->score += score;

        //audio_manager::get()->play_sound("explosion", 0);
    } else {
        grid[row][col]->dont_check(); // If no points were scored, don't check this block anymore
    }
}

block_type grid::validate_block(int row, int col) {
    if (row < 0 || row >= GRID_MAX_ROWS || col < 0 || col >= GRID_MAX_COLUMNS || !grid[row][col]) {
        // If we are out of bounds or there is nothing in this position, return "false"
        return BLOCK_TYPE_NOGOOD;
    }

    if (grid[row][col]) {
        // If there is a block but it is falling or dead, return "false"
        if (grid[row][col]->falling() || grid[row][col]->dead()) {
            return BLOCK_TYPE_NOGOOD;
        }
    }

    return grid[row][col]->block_type();
}

void grid::set_width(int width) {
    this->width = width;
}

void grid::set_height(int height) {
    this->height = height;
}

bool grid::is_game_over() {
    for (int i = 0; i < GRID_MAX_COLUMNS; ++i) {
        if (grid[0][i]) {
            if (!grid[0][i]->falling()) {
                return true;
            }
        }
    }

    return false;
}

bool grid::spawning() const {
    return spawning;
}

void Grid::set_block_empty(int row, int col) {
    grid[row][col] = nullptr;
}

void grid::set_block(const block* block, int row, int col) {
    if (row >= GRID_MAX_ROWS || col >= GRID_MAX_COLUMNS || !block) {
        return;
    }

    grid[row][col] = block;
}

block* grid::get_block(int row, int col) {
    if (row < 0 || row >= GRID_MAX_ROWS || col < 0 || col >= GRID_MAX_COLUMNS) {
        return nullptr;
    }

    return grid[row][col];
}

int grid::get_row_y_coord(int row) {
    return (50 + (row * BLOCK_HEIGHT));
}

int grid::get_col_x_coord(int col) {
    return (220 + (col * BLOCK_WIDTH));
}

int grid::width() const {
    return _width;
}

int grid::height() const {
    return _height;
}

int grid::combos() const {
    return _combos;
}

int grid::score() const {
    return _score;
}

void grid::spawn_blocks(int dt) {
    spawn_time_left -= dt;

    if (spawn_time_left <= 0) {
        spawn_time_left = start_spawn_interval;

        // Spawn a new block if we are still in a row below 6
        if (spawn_row > 6) {
            int random          = rand() % 5;
            int left_spawn_col  = (spawn_col - 1 < 0 ? spawn_col : spawn_col - 1);
            int below_spawn_row = (spawn_row == GRID_MAX_ROWS - 1 ? spawn_row : spawn_row + 1);

            if (left_spawn_col != spawn_col) {
                if (grid[spawn_row][left_spawn_col]) {
                    if (grid[spawn_row][leftspawn_col]->block_type() == static_cast<block_type>(random)) {
                        random = (random - 1 < 0 ? 4 : random - 1);
                    }
                }
            }

            if (below_spawn_row != spawn_row) {
                if (grid[below_spawn_row][spawn_col]) {
                    if (grid[below_spawn_row][spawn_col]->block_type() == static_cast<block_type>(random)) {
                        random = (random - 1 < 0 ? 4 : random - 1);
                    }
                }
            }

            block* block    = new block(static_cast<block_type>(random), spawn_row, spawn_col);
            block->position = vector(get_col_x_coord(spawn_col), -BLOCK_HEIGHT);
            block->speed    = vector(0, SPAWN_DROP_SPEED);
            block->set_drop_y(get_row_y_coord(spawn_row));
            grid[spawn_row][spawn_col] = block;
            block = nullptr;

            // Decrease row count if entire row has been spawned...
            if (spawn_col >= GRID_MAX_COLUMNS - 1) {
                spawn_col = 0;
                --spawn_row;
            } else {
                // ...or move along
                ++spawncol;
            }
        }

        // If the last spawned block has reached its destination, stop spawning
        if (grid[GRID_MAX_ROWS/2][GRID_MAX_COLUMNS - 1]) {
            if (grid[GRID_MAX_ROWS/2][GRID_MAX_COLUMNS - 1]->position.y == get_row_y_coord(GRID_MAX_ROWS/2)) {
                spawning = false;

                if(game::game_settings.cf_mode_unlocked) {
                    audio_manager::get()->play_sound("moves", 0);
                }
            }
        }
    }
}

int grid::final_score() {
    return score;// + COMBO_POINTS * combos;
}

int grid::highest_block() {
    for (int row = 0; row < GRID_MAX_ROWS; ++row) {
        for (int col = 0; col < GRID_MAX_COLUMNS; ++col) {
            if (grid[row][col]) {
                if (! grid[row][col]->falling() && !grid[row][col]->dead()) {
                    return row;
                }
            }
        }
    }
}

void grid::print_grid() {
    for (int row = 0; row < GRID_MAX_ROWS; row++) {
        for (int col = 0; col < GRID_MAX_COLUMNS; col++) {
            if (grid[row][col]) {
                if (grid[row][col]->falling()) {
                    std::cout << "F";
                } else if (grid[row][col]->dead()) {
                    std::cout << "D";
                } else if (grid[row][col]->swapping()) {
                    std::cout << "S";
                } else {
                    std::cout << "N";
                }
            } else {
                std::cout << "0";
            }

            if (col == 7) {
                std::cout << endl;
            }
        }
    }

    std::cout << endl;
}
