#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
// #include <stdarg.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

enum {
    _SSD1306_IOC_CLEAR_ = ('p')<<8,
    _SSD1306_IOC_HOME_,
    _SSD1306_IOC_NORMAL_,
    _SSD1306_IOC_INVERT_,
    _SSD1306_IOC_CLR_PAGE_,
    _SSD1306_IOC_SET_PAGE_
};

enum{
    _CMD_CLEAR_,
    _CMD_HOME_,
    _CMD_NORMAL_,
    _CMD_INVERT_,
    _CMD_CLR_PAGE_,
    _CMD_SET_PAGE_,
    _CMD_SEND_STRING_,
    _CMD_EXIT_
};

int main () {
    // FILE * fp;
    int fd, ret, cmd, fila;
    char data[129] = " MsE 4Co 2019!   IMPLEMENTACION  DE MANEJADORES DE DISPOSITIVOS                  Seleccione una opcion del menu    en consola";

    fd = open("/dev/mseSSD1306" , O_RDWR);
    assert(fd > 0);
    ioctl(fd, _SSD1306_IOC_CLEAR_);
    write(fd, data, sizeof(data));

    do{
        printf("\n");
        printf("Introduzca %d para borrar pantalla\n", _CMD_CLEAR_ );
        printf("Introduzca %d para ir al inicio\n", _CMD_HOME_ );
        printf("Introduzca %d para pantalla normal\n", _CMD_NORMAL_ );
        printf("Introduzca %d para pantalla invertida\n", _CMD_INVERT_ );
        printf("Introduzca %d para borrar fila\n", _CMD_CLR_PAGE_ );
        printf("Introduzca %d para direccionar fila\n", _CMD_SET_PAGE_ );
        printf("Introduzca %d para enviar string\n", _CMD_SEND_STRING_ );
        printf("Introduzca %d para salir\n", _CMD_EXIT_ );
        
        printf("Accion: ");
        scanf("%d", &cmd);

        switch (cmd)
        {
            case _CMD_CLEAR_:
                ret = ioctl(fd, _SSD1306_IOC_CLEAR_);
                assert(ret == 0);
                break;

            case _CMD_HOME_:
                ret = ioctl(fd, _SSD1306_IOC_HOME_);
                assert(ret == 0);
                break;

            case _CMD_NORMAL_:
                ret = ioctl(fd, _SSD1306_IOC_NORMAL_);
                assert(ret == 0);
                break;

            case _CMD_INVERT_:
                ret = ioctl(fd, _SSD1306_IOC_INVERT_);
                assert(ret == 0);
                break;

            case _CMD_CLR_PAGE_:
                printf("Introduzca el # de fila (0-7): ");
                scanf("%d", &fila);
                ret = ioctl(fd, _SSD1306_IOC_CLR_PAGE_, fila);
                assert(ret == 0);
                break;

            case _CMD_SET_PAGE_:
                printf("Introduzca el # de fila (0-7): ");
                scanf("%d", &fila);
                ret = ioctl(fd, _SSD1306_IOC_SET_PAGE_, fila);
                assert(ret == 0);
                break;

            case _CMD_SEND_STRING_:
                printf("Introduzca la cadena de caracteres: ");
                scanf("%s", data);
                write(fd, data, strlen(data));
                break;
            
            case _CMD_EXIT_:
                printf("Bye Bye\n");
                break;

            default:
                printf("Opción Inválida\n");
                break;
        }

    } while( _CMD_EXIT_ != cmd );

    close(fd);

    return 0;
}

/*
arm-linux-gnueabihf-gcc -static testOLED.c -o testOLED
*/