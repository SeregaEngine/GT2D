#ifndef GTCOMMAND_H_
#define GTCOMMAND_H_

/* ====== DEFINES ====== */
enum eGTCommand
{
    GTC_MOVE_UP = 0,
    GTC_MOVE_LEFT,
    GTC_MOVE_DOWN,
    GTC_MOVE_RIGHT,
    GTC_ATTACK,
};

/* ====== STRUCTURES ====== */
// Actors handle commands by themselves
struct GT_Command
{
    s32 cmd;
    TList<f32> lstArgument;

    GT_Command() = default;
    GT_Command(s32 _cmd) : cmd(_cmd), lstArgument() {}
    GT_Command(s32 _cmd, TList<f32>& _lstArgument) : cmd(_cmd), lstArgument(_lstArgument) {}
};

#endif // GTCOMMAND_H_