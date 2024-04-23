#ifndef RES_MD_SHIP_H
#define RES_MD_SHIP_H

enum MD_SHIP_RES_FILE_ID { // IDs and indexes are synced
    /* BCKS */
    MD_SHIP_BCK_MD_OJIGI=0x7,
    MD_SHIP_BCK_MD_RUN=0x8,
    MD_SHIP_BCK_MD_SHIPTALK01=0x9,
    MD_SHIP_BCK_MD_SHIPWAIT=0xA,
    MD_SHIP_BCK_MD_SHIPWAIT02=0xB,
    MD_SHIP_BCK_MD_TALK01=0xC,
    MD_SHIP_BCK_MD_WAIT01=0xD,
    MD_SHIP_BCK_MD_WALK=0xE,
    MD_SHIP_BCK_MDARM_OJIGI=0xF,
    MD_SHIP_BCK_MDARM_RUN=0x10,
    MD_SHIP_BCK_MDARM_SHIPTALK01=0x11,
    MD_SHIP_BCK_MDARM_SHIPWAIT=0x12,
    MD_SHIP_BCK_MDARM_SHIPWAIT02=0x13,
    MD_SHIP_BCK_MDARM_TALK01=0x14,
    MD_SHIP_BCK_MDARM_WAIT01=0x15,
    MD_SHIP_BCK_MDARM_WALK=0x16,
    
    /* BDLM */
    MD_SHIP_BDL_MD=0x19,
    MD_SHIP_BDL_MD_HARP=0x1A,
    MD_SHIP_BDL_MDARM=0x1B,
    MD_SHIP_BDL_YMDHP00=0x1C,
    
    /* BTK */
    MD_SHIP_BTK_YMDHP00=0x1F,
    
    /* BTP */
    MD_SHIP_BTP_FUAN=0x22,
    MD_SHIP_BTP_MABA=0x23,
    MD_SHIP_BTP_MD_CAUGHT=0x24,
    MD_SHIP_BTP_MD_FALL=0x25,
    MD_SHIP_BTP_MD_FALL02=0x26,
    MD_SHIP_BTP_MD_FLY02=0x27,
    MD_SHIP_BTP_MD_HARPPLAY=0x28,
    MD_SHIP_BTP_MD_KAMAE=0x29,
    MD_SHIP_BTP_MD_KAMAEWAIT=0x2A,
    MD_SHIP_BTP_MD_KOMARI=0x2B,
    MD_SHIP_BTP_MD_KYORO2=0x2C,
    MD_SHIP_BTP_MD_LAND=0x2D,
    MD_SHIP_BTP_MD_LAND02=0x2E,
    MD_SHIP_BTP_MD_PIYO2=0x2F,
    MD_SHIP_BTP_MD_WATASU=0x30,
    
    /* DAT */
    MD_SHIP_BTI_MD_SPOT=0x33,
};

#endif /* RES_MD_SHIP_H */