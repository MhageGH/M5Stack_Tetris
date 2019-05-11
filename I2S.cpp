#include "I2S.h"

void I2S_Init()
{
  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_DAC_BUILT_IN | I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = 8000,                          // not work when SAMPLE_RATE < 8000
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // not work when using 8bit
      .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT, // monoral. set right data only
                                                    // (need both data when using I2S_CHANNEL_FMT_ALL_RIGHT)
      .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S_MSB),
      .intr_alloc_flags = 0,
      .dma_buf_count = 32, // set data before all the buffers are empty
      .dma_buf_len = 64,
      .use_apll = false};
  i2s_driver_install((i2s_port_t)0, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)0, NULL);
}

void I2S_Write(char *data, int numData)
{
  size_t bytes_written;
  i2s_write_expand((i2s_port_t)0, (const char *)data, numData, 8, 16, &bytes_written, portMAX_DELAY); // input unsigned 8bit data, I2S outputs unsigned 16bit data.
}

void I2S_Stop()
{
  i2s_stop((i2s_port_t)0);
}
