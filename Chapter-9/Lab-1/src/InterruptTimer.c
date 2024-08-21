#include "psp_api.h"
#include "bsp_external_interrupts.h"
#include "psp_ext_interrupts_eh1.h"
#include "bsp_timer.h"
#include "bsp_printf.h"

#define SegEn_ADDR      0x80001038
#define SegDig_ADDR     0x8000103C

#define GPIO_SWs        0x80001400
#define GPIO_LEDs       0x80001404
#define GPIO_INOUT      0x80001408
#define RGPIO_INTE      0x8000140C
#define RGPIO_PTRIG     0x80001410
#define RGPIO_CTRL      0x80001418
#define RGPIO_INTS      0x8000141C

#define RPTC_CNTR       0x80001200
#define RPTC_HRC        0x80001204
#define RPTC_LRC        0x80001208
#define RPTC_CTRL       0x8000120c

#define Select_INT      0x80001018

unsigned int count = 0;

extern D_PSP_DATA_SECTION D_PSP_ALIGNED(1024) pspInterruptHandler_t G_Ext_Interrupt_Handlers[8];

void GPIO_ISR(void)
{
    unsigned int i;

    /* Write the LED */
    i = M_PSP_READ_REGISTER_32(GPIO_LEDs);             /* RGPIO_OUT */
    i = !i;                                            /* Invert the LEDs */
    i = i & 0x1;                                       /* Keep only the right-most LED */
    M_PSP_WRITE_REGISTER_32(GPIO_LEDs, i);             /* RGPIO_OUT */

    /* Clear GPIO interrupt */
    M_PSP_WRITE_REGISTER_32(RGPIO_INTS, 0x0);           /* Clear GPIO Interrupt Status */

    /* Stop the generation of the specific external interrupt */
    bspClearExtInterrupt(4);
}

void PTC_ISR(void)
{
    /* Increment 7-Segment Displays */
    M_PSP_WRITE_REGISTER_32(SegDig_ADDR, count);
    count++;
    
    /* Clear PTC interrupt */
    M_PSP_WRITE_REGISTER_32(RPTC_CNTR, 0x0);
    M_PSP_WRITE_REGISTER_32(RPTC_CTRL, 0x40);
    M_PSP_WRITE_REGISTER_32(RPTC_CTRL, 0x31);
      
   /* Stop the generation of the specific external interrupt */
   bspClearExtInterrupt(3);
}

void DefaultInitialization(void)
{
    u32_t uiSourceId;

    /* Register interrupt vector */
    pspInterruptsSetVectorTableAddress(&M_PSP_VECT_TABLE);

    /* Set external-interrupts vector-table address in MEIVT CSR */
    pspExternalInterruptSetVectorTableAddress(G_Ext_Interrupt_Handlers);

    /* Initialize the generation register */
    bspInitializeGenerationRegister(D_PSP_EXT_INT_ACTIVE_HIGH);

    /* Clear all external interrupts */
    for (uiSourceId = D_BSP_FIRST_IRQ_NUM; uiSourceId <= D_BSP_LAST_IRQ_NUM; uiSourceId++)
    {
        bspClearExtInterrupt(uiSourceId);
    }

    /* Set standard priority order */
    pspExtInterruptSetPriorityOrder(D_PSP_EXT_INT_STANDARD_PRIORITY);

    /* Set interrupt threshold to minimal (serve all interrupts) */
    pspExtInterruptsSetThreshold(M_PSP_EXT_INT_THRESHOLD_UNMASK_ALL_VALUE);
    pspExtInterruptsSetNestingPriorityThreshold(M_PSP_EXT_INT_THRESHOLD_UNMASK_ALL_VALUE);
}

void ExternalIntLine_Initialization(u32_t uiSourceId, u32_t priority, pspInterruptHandler_t pTestIsr)
{
    /* Configure external interrupt */
    pspExtInterruptSetType(uiSourceId, D_PSP_EXT_INT_LEVEL_TRIG_TYPE);
    pspExtInterruptSetPolarity(uiSourceId, D_PSP_EXT_INT_ACTIVE_HIGH);
    pspExtInterruptClearPendingInt(uiSourceId);
    pspExtInterruptSetPriority(uiSourceId, priority);
    pspExternalInterruptEnableNumber(uiSourceId);

    /* Register the ISR */
    G_Ext_Interrupt_Handlers[uiSourceId] = pTestIsr;
}

void PTC_Initialization(void)
{
    /* Initialize and start the PTC */
    M_PSP_WRITE_REGISTER_32(RPTC_CNTR, 0x0);           /* Set initial counter value */
    M_PSP_WRITE_REGISTER_32(RPTC_LRC, 50000);          /* Set counter limit*/
    M_PSP_WRITE_REGISTER_32(RPTC_CTRL, 0xC0);         /* Reset counter */    
    M_PSP_WRITE_REGISTER_32(RPTC_CTRL, 0x31);           /* De-assert reset and Enable the PTC */  
     
}

void GPIO_Initialization(void)
{
    /* Configure LEDs and Switches */
    M_PSP_WRITE_REGISTER_32(GPIO_INOUT, 0xFFFF);        /* GPIO_INOUT */
    M_PSP_WRITE_REGISTER_32(GPIO_LEDs, 0x0);            /* GPIO_LEDs */

    /* Configure GPIO interrupts */
    M_PSP_WRITE_REGISTER_32(RGPIO_INTE, 0x10000);       /* RGPIO_INTE */
    M_PSP_WRITE_REGISTER_32(RGPIO_PTRIG, 0x10000);      /* RGPIO_PTRIG */
    M_PSP_WRITE_REGISTER_32(RGPIO_INTS, 0x0);           /* Clear Interrupt Status */
    M_PSP_WRITE_REGISTER_32(RGPIO_CTRL, 0x1);           /* Enable GPIO */
}

int main(void)
{
    //int count = 0;

    /* Initialize the interrupt system */
    DefaultInitialization();                            /* Default initialization */
    pspExtInterruptsSetThreshold(5);                    /* Set interrupts threshold to 5 */

    /* Initialize interrupt lines */
    ExternalIntLine_Initialization(4, 9, GPIO_ISR);     /* Initialize IRQ4 for GPIO ISR */
    ExternalIntLine_Initialization(3, 6, PTC_ISR);      /* Initialize IRQ3 for PTC ISR */

    M_PSP_WRITE_REGISTER_32(Select_INT, 0x3);  // Set both bit 0 (irq_gpio_enable) and bit 1 (irq_ptc_enable)
    
    /* Initialize peripherals */
    GPIO_Initialization();                              /* Initialize GPIO */
    M_PSP_WRITE_REGISTER_32(SegEn_ADDR, 0x0);           /* Initialize the 7-Segment Displays */
    PTC_Initialization();                               /* Initialize PTC */
    
    /* Enable interrupts */
    pspInterruptsEnable();                              /* Enable all interrupts in mstatus CSR */
    M_PSP_SET_CSR(D_PSP_MIE_NUM, D_PSP_MIE_MEIE_MASK);  /* Enable external interrupts in mie CSR */

    while (1) {
    }
    return(0);
}

