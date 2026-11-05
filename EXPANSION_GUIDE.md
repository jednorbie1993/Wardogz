# Wardogz RPG Expansion

Built from the supplied Wardogz(6).zip. No personal save, backup, prebuilt executable, object files, or Git history is distributed.

## Install and build (Windows)

1. Close Wardogz. Keep your existing game folder and save.dat.
2. For manual replacement, copy the ten listed C/header files to the matching paths below; rpg.c and rpg.h are new. The existing build.bat already compiles root C files. The updated build.bat also sets its working directory correctly.
3. Alternatively, extract the complete ZIP to a separate folder and copy your own save.dat into that Wardogz folder. Do not replace your original folder until you have verified your progress.
4. Run build.bat with GCC/w64devkit available on PATH, or run mingw32-make clean followed by mingw32-make. Recompile from source; do not use the previous wardogz.exe.
5. Open Wardogz > Equipment / Store / Items. Choose 9 to claim equipment for previously defeated bosses. No Campaign replay or reset is needed.

## Save compatibility

Dog and GameData layouts are unchanged (13,152 and 13,240 bytes). A legacy save is read and validated before any migration. The migration initializes separate expansion state; every original character/progress byte remains unchanged. The first successful save preserves the previous file as save.dat.legacy.bak, then writes a temporary file and replaces save.dat. The original 13,240-byte layout remains the prefix. A 20-byte version/length/checksum header and 224-byte RPG payload follow it. Total new size: 13,484 bytes.

The checksum covers the legacy character data and expansion payload. Truncated, corrupt, unsupported-version, or incompatible-layout saves are rejected without starting a new character or overwriting the save. Loading is transactional. Save writes are blocked during battle so equipment and serum bonuses cannot enter the saved base stats.

Use the updated game to retain expansion progress. Running the old executable may discard the appended expansion data when it saves. Keep the backup for rollback; loading that backup into the updated game begins a fresh expansion migration with the old character progress.

Legacy eligibility uses each cleared zone counter for its final-opponent reward, the five explicit secret-boss defeat flags, and final Campaign completion for Project Cerberus. It does not assume that a secret boss was defeated merely because its area was cleared. In the supplied save, 14 zone-final rewards are eligible. Claiming sets a persistent bit per reward; selling an item does not make its old claim available again. Defeating the boss again is a new drop, and an already-owned item converts to coins.

## Systems and controls

- Six gear slots: Head, Body, Neck, Paws, Fangs, Earrings. Equipment is owned once, and all worn gear retains its passive effects.
- The existing normal skill slots still unlock through Arena rank, up to eight. Two separate gear skills use battle choices 9 and 10. They never occupy or alter normal skill slots. Up to two skill-granting items activate automatically; with three or more, the equipment menu lets you choose any two. Existing selections remain active until changed or unequipped.
- Battle action 5 opens Items. Food works at Home and in battles. Using a battle item consumes your turn; invalid/cancelled item choices do not. Serums can only be used in Campaign/Arena, once per type per battle, and expire on victory, defeat, or surrender.
- Energy is the existing fatigue field (a higher value means more usable Energy). Food respects the existing maximum HP/Energy.
- Store Buy/Sell uses Battle Coins. Store gear has both Level and Arena-rank requirements; owned gear has a Level requirement for equipping. Equipped items must be removed before sale. All gear and consumables sell for half their listed price. No inventory can exceed 999 consumables per type.
- Level increases from cumulative EXP, capped at 99, and never automatically changes base stats or Arena rank. Level L requires another 100 × L EXP to reach L+1. Existing saves begin the expansion at Level 1, with no guessed retroactive EXP or coins.
- Campaign tier = floor(zone index / 4) + 1. Victory gives 20 × tier EXP and 12 × tier coins. Each zone's last regular opponent and each of the five secret bosses gives double rewards plus its guaranteed unique item. Elite variants do not independently grant the zone-final drop.
- Arena victory tier is F=1 through SSS=9. Rewards are 20 × tier EXP and 12 × tier coins. Loss, surrender, Training, and Sparring give no expansion victory rewards. Existing Arena progression and unlocks remain.
- Gear growth bonuses add to each of the existing three randomly chosen battle stat gains. They do not grant additional selected stats or raise the 999 permanent-stat cap.
- Gear ATK/DEF/SPD bonuses are temporary combat values. Save data and Home base stats stay separate. Existing attack-skill behavior is retained when removing gear/serum ATK additions. DEF/SPD temporary changes are reset before victory growth so earned gains remain.
- Poison: 3 enemy turns, damage = floor(enemy max HP / 50) + 1. Bleed: 8 damage for 3 enemy turns. Stun: skip one enemy turn. Paralysis: 40% skip chance for 3 enemy turns. Each worn effect has a 15% proc chance per successful damaging skill hit. Reapplication refreshes duration. These gear effects are separate from existing skill statuses and expire at battle end.
- Gear Shock: 30 power, 18 Energy, 90 accuracy, 35% stun chance on hit. Gear Venom: 30 power, 18 Energy, 90 accuracy, guaranteed poison on hit. Gear Rush: 40 power, 18 Energy, 90 accuracy. The existing combat formula interprets power and accuracy. Insufficient Energy rejects gear skills without consuming a turn.
- Meat restores 80 HP (20 coins); Energy Meal restores 60 Energy (20); Full Meal restores 120 HP and 80 Energy (45). Power/Guard/Speed Serum adds 25 ATK/DEF/SPD for the current battle (50 each; buying requires Level 3, Arena E).

Item names, prices, proc rates, rewards, and leveling values are implementation defaults: the retrieved discussion confirmed system behavior but did not provide an exact balance table. Gear definitions are centralized in rpg.c for adjustment.

## File-by-file changes

| File | Change |
|---|---|
| rpg.h (new) | Separate expansion state, equipment definitions, constants, and system interfaces; no changes to Dog or GameData. |
| rpg.c (new) | 38 equipment items, 6 consumables, equipment/Store UI, EXP/coins, all 26 boss rewards, legacy claims, gear skills, passives, and temporary combat bonuses. |
| save.c | Frozen legacy ABI checks, validated transactional loading, backward-compatible migration, versioned/checksummed extension, original backup, temporary-file replacement, and battle-save protection. |
| save.h | Documents load return values: loaded, missing, or invalid. Original structures remain identical. |
| main.c | Initializes expansion state, refuses to replace an invalid save with a new character, and adds Equipment / Store / Items under Wardogz. |
| menu_shortcuts.c | Correctly treats invalid-load results as failure. Existing Home Rest Count reset and save remain intact. |
| battle.c | Campaign gear/item actions, passive turns, rewards, and cleanup on every battle exit. Moves DEF/SPD restoration before victory stat growth so growth is not erased. |
| arena/arena.c | Same integration for Arena while retaining F–SSS progression and normal skill-slot unlocks. |
| skill.c | Triggers gear passives only after successful damaging hits by the active Campaign/Arena player; leaves Sparring unaffected. |
| stat.c | Adds equipped growth bonuses to the existing three-stat victory reward. |
| makefile | Header dependency tracking, clean targets, automatic inclusion of rpg.c; removes old stray command examples from recipes. |
| build.bat | Builds/runs from its own directory, retaining the existing compiler flags and source groups. |
| tests/ | Synthetic regression tests, Windows-call stubs for Linux logic testing, and isolated test runner. No personal save fixture. |

Unmodified source, guides, license, and README are included. The supplied project uses console text; there were no separate image/audio asset files to add.

## Validation and limitations

- Before changing save code: compiled the original loader and verified a byte-for-byte load of the supplied 13,240-byte save and its ABI.
- After implementation: migration and repeated save/load preserve every byte of original character/progress data. Original input save remains unchanged.
- Verified 14 eligible claims in the supplied save, zero duplicate claims after reload/sale, all 26 claims in an all-boss synthetic fixture, final-completion fallback, and duplicate-to-coin conversion.
- Tested truncated saves, bad version/checksum, invalid-load state preservation, and refusal to overwrite invalid data.
- Tested equipment requirements, Store ownership/rank/level checks, buy/sell, 3 gear skills selecting 2, normal-slot preservation, food caps, serum restrictions/expiry, all four gear statuses, EXP without automatic stats, and growth bonuses.
- Executed actual Campaign and Arena victory, defeat, and surrender loops. Verified no expansion rewards for defeat/surrender and temporary bonus cleanup. Home reset was saved and reloaded successfully.
- Full source compiled with GCC C11, -Wall -Wextra. AddressSanitizer and UndefinedBehaviorSanitizer tests passed. LeakSanitizer was disabled because this runtime cannot inspect processes under its tracing environment.
- Windows APIs were replaced only in the Linux test build with timing/audio stubs. Native Windows compilation, console rendering/audio, the real five-minute timer, power-loss behavior, and a complete interactive Campaign playthrough could not be tested. No Windows executable is included. Build it on Windows using the included build.bat.

To rerun the synthetic logic suite on Linux with GCC: sh tests/run_tests.sh. The runner creates an isolated temporary directory and never opens or writes your live save.dat. Native Windows game builds do not include the test shim headers.
