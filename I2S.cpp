#include "I2S.h"

void I2S_Init()
{
  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_DAC_BUILT_IN | I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT, //2-channels
      .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S_MSB),
      .intr_alloc_flags = 0,
      .dma_buf_count = 128,
      .dma_buf_len = 64,
      .use_apll = false};
  i2s_driver_install((i2s_port_t)0, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)0, NULL);
}

void I2S_Write(char *data, int numData)
{
  i2s_write_bytes((i2s_port_t)0, (const char *)data, numData, portMAX_DELAY);
}

void I2S_Stop()
{
  i2s_driver_uninstall((i2s_port_t)0);
}
