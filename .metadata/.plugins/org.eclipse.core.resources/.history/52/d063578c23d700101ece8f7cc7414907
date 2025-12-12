#include "fsm_manual.h"

void manual_init(void)
{
    manual_state = MANUAL_WAIT_STATE;
}
uint8_t wait_switch_flag = 0;
/*
 * FSM MANUAL (Kiểu A):
 * BTN4 → vào MANUAL
 * BTN2 → đổi DO↔XANH
 * BTN1 → thoát MANUAL
 */
void fsm_manual_run(void)
{
    /* ================= THOÁT MANUAL (BTN1) ================= */
    if (system_state == MANUAL_STATE && is_button_pressed(0))
    {
        system_state = NORMAL_STATE;
        manual_state = MANUAL_WAIT_STATE;
        wait_switch_flag = 0;
        return;
    }

    /* ================= VÀO MANUAL (BTN4) ================= */
    if (system_state == NORMAL_STATE && is_button_pressed(3))
    {
        system_state = MANUAL_STATE;
        manual_state = MANUAL_WAIT_STATE;

        Manual_Wait_Second = 0;
        setTimer0(1000);   // đếm giây
        wait_switch_flag = 0;

        return;
    }

    /* Không ở MANUAL thì bỏ qua */
    if (system_state != MANUAL_STATE) return;

    /* ====================================================== */
    /*                     MANUAL MODE                        */
    /* ====================================================== */

    switch (manual_state)
    {
        /* ---------- CHỜ 3 GIÂY AN TOÀN LÚC VÀO MANUAL ---------- */
        case MANUAL_WAIT_STATE:
            if (timer0_flag)
            {
                timer0_flag = 0;
                Manual_Wait_Second++;

                if (Manual_Wait_Second >= MANUAL_WAIT_TIME)
                {
                    manual_state = MANUAL_SWITCH_STATE;
                }

                setTimer0(1000);
            }
            break;

        /* ---------- TRẠNG THÁI CHÍNH ---------- */
        case MANUAL_SWITCH_STATE:

            /* BTN2 → bắt đầu đếm 3 giây để chuyển đèn */
            if (is_button_pressed(1) && wait_switch_flag == 0)
            {
                wait_switch_flag = 1;
                setTimer1(3000);   // bắt đầu chờ 3 giây
            }

            /* Khi timer1 hết → đổi đèn */
            if (wait_switch_flag && timer1_flag)
            {
                timer1_flag = 0;
                wait_switch_flag = 0;

                if (light_state1 == RED_STATE) {
                    light_state1 = GREEN_STATE;
                    light_state2 = RED_STATE;
                } else {
                    light_state1 = RED_STATE;
                    light_state2 = GREEN_STATE;
                }
            }

            break;
    }

    /* ================== Cập nhật đèn ================== */
    if (light_state1 == RED_STATE)
    {
        RGB_TrafficLight_TurnOn(RGB_tl1, RED_STATE);
        RGB_TrafficLight_TurnOn(RGB_tl2, GREEN_STATE);
    }
    else
    {
        RGB_TrafficLight_TurnOn(RGB_tl1, GREEN_STATE);
        RGB_TrafficLight_TurnOn(RGB_tl2, RED_STATE);
    }

    /* ================== Cập nhật LCD ================== */
    updateLCDBuffer();
}
