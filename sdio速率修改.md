3399的WIFI速率50M改成150
```
&sdio0 {
clock-frequency = <150000000>;
clock-freq-min-max = <200000 150000000>;
supports-sdio;
bus-width = <4>;
disable-wp;
cap-sd-highspeed;
cap-sdio-irq;
keep-power-in-suspend;
mmc-pwrseq = <&sdio_pwrseq>;
non-removable;
num-slots = <1>;
pinctrl-names = "default";
pinctrl-0 = <&sdio0_bus4 &sdio0_cmd &sdio0_clk>;
sd-uhs-sdr104;
status = "okay";
};
```

```
--- a/drivers/mmc/core/sdio.c
+++ b/drivers/mmc/core/sdio.c
@@ -193,7 +193,7 @@ static int sdio_read_cccr(struct mmc_card *card, u32 ocr)
                if (!card->sw_caps.sd3_bus_mode) {
                        if (speed & SDIO_SPEED_SHS) {
                                card->cccr.high_speed = 1;
-                               card->sw_caps.hs_max_dtr = 50000000;
+                               card->sw_caps.hs_max_dtr = 150000000;
                        } else {
                                card->cccr.high_speed = 0;
                                card->sw_caps.hs_max_dtr = 25000000;
@@ -375,7 +375,7 @@ static unsigned mmc_sdio_get_max_clock(struct mmc_card *card)
                 * high-speed, but it seems that 50 MHz is
                 * mandatory.
                 */
-               max_dtr = 50000000;
+               max_dtr = 150000000;
        } else {
                max_dtr = card->cis.max_dtr;
        }
```

除了dts改，最大限制也要从50改成150

修改限制也可以直接修改到sdio clk
```
diff --git a/drivers/mmc/core/sdio.c b/drivers/mmc/core/sdio.c
index 010ea232612..6a3cc51356b 100644
--- a/drivers/mmc/core/sdio.c
+++ b/drivers/mmc/core/sdio.c
@@ -193,10 +193,10 @@ static int sdio_read_cccr(struct mmc_card *card, u32 ocr)
                if (!card->sw_caps.sd3_bus_mode) {
                        if (speed & SDIO_SPEED_SHS) {
                                card->cccr.high_speed = 1;
-                               card->sw_caps.hs_max_dtr = 50000000;
+                               card->sw_caps.hs_max_dtr = 2000000;
                        } else {
                                card->cccr.high_speed = 0;
-                               card->sw_caps.hs_max_dtr = 25000000;
+                               card->sw_caps.hs_max_dtr = 2000000;
                        }
                }
        }
@@ -375,7 +375,7 @@ static unsigned mmc_sdio_get_max_clock(struct mmc_card *card)
                 * high-speed, but it seems that 50 MHz is
                 * mandatory.
                 */
-               max_dtr = 50000000;
+               max_dtr = 2000000;
        } else {
                max_dtr = card->cis.max_dtr;
        }

```
