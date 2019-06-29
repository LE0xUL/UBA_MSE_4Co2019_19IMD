// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>

static const struct i2c_device_id mse24lc256_i2c_id[] = {
    { "mse24lc256", 0 },
    { }
};

MODULE_DEVICE_TABLE(i2c, mse24lc256_i2c_id);

static const struct of_device_id mse24lc256_of_match[] = {
    { .compatible = "trec,mse24lc256" },
    { }
};

MODULE_DEVICE_TABLE(of, mse24lc256_of_match);

static int mse24lc256_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    int rv;
    char buf[10] = {0, 0};
    char data[] = "MsE1!";
    pr_info("mse24lc256_probe!\n");
    
    /* escribo 2 bytes de address + 6 de datos */
    memcpy(buf+2, data, 6);
    rv = i2c_master_send(client, buf, 8);
    pr_info("i2c_master_send: %d\n", rv);
    
    return 0;
}

static int mse24lc256_remove(struct i2c_client *client)
{
    char buf[2] = {0, 2};
    char data[10];
    int rv;
    pr_info("mse24lc256_remove!\n");

    /* escribo 2 bytes de address */
    rv = i2c_master_send(client, buf, 2);
    pr_info("i2c_master_send: %d\n", rv);

    /* leo 6 bytes de datos */
    rv = i2c_master_recv(client, data, 4);
    pr_info("i2c_master_recv: %d data:%s 0x%02X\n", rv, data, data[0]);

    return 0;
}

static struct i2c_driver mse24lc256_i2c_driver = {
    .driver = {
        .name = "mse24lc256",
        .of_match_table = mse24lc256_of_match,
    },
    .probe = mse24lc256_probe,
    .remove = mse24lc256_remove,
    .id_table = mse24lc256_i2c_id
};

module_i2c_driver(mse24lc256_i2c_driver);

/**********************************************************************/
/* Modules licensing/description block.                               */
/**********************************************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("@trecetp Leonardo Urrego");
MODULE_DESCRIPTION("MSE4Co.19IMD Kernel Module EEprom 24LC256 I2C");
