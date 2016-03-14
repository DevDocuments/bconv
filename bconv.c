#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define n int32_t
#define un uint32_t

static const char *pn;

static un atoi(const char *str, const uint8_t base) {
    if ((base < 2) || (base > 36))
        return 0;
    un value = 0;
    while (*str != '\0') {
        value *= base;
        switch (*str) {
          case '0':           value +=  0; break;
          case '1':           value +=  1; break;
          case '2':           value +=  2; break;
          case '3':           value +=  3; break;
          case '4':           value +=  4; break;
          case '5':           value +=  5; break;
          case '6':           value +=  6; break;
          case '7':           value +=  7; break;
          case '8':           value +=  8; break;
          case '9':           value +=  9; break;
          case 'a': case 'A': value += 10; break;
          case 'b': case 'B': value += 11; break;
          case 'c': case 'C': value += 12; break;
          case 'd': case 'D': value += 13; break;
          case 'e': case 'E': value += 14; break;
          case 'f': case 'F': value += 15; break;
          case 'g': case 'G': value += 16; break;
          case 'h': case 'H': value += 17; break;
          case 'i': case 'I': value += 18; break;
          case 'j': case 'J': value += 19; break;
          case 'k': case 'K': value += 20; break;
          case 'l': case 'L': value += 21; break;
          case 'm': case 'M': value += 22; break;
          case 'n': case 'N': value += 23; break;
          case 'o': case 'O': value += 24; break;
          case 'p': case 'P': value += 25; break;
          case 'q': case 'Q': value += 26; break;
          case 'r': case 'R': value += 27; break;
          case 's': case 'S': value += 28; break;
          case 't': case 'T': value += 29; break;
          case 'u': case 'U': value += 30; break;
          case 'v': case 'V': value += 31; break;
          case 'w': case 'W': value += 32; break;
          case 'x': case 'X': value += 33; break;
          case 'y': case 'Y': value += 34; break;
          case 'z': case 'Z': value += 35; break;
          default: return 0;
        }
        str++;
    }
    return value;
}

static char *itoa(un value, const uint8_t base) {
    if ((base < 2) || (base > 36))
        return "";
    char *rc = NULL;
    {
        size_t rc_len = 0;
        do {
            /* TODO: Instead of using `realloc`, calculate the number of digits
             * and allocate once. */
            rc = realloc(rc, (sizeof (char)) * (++rc_len + 1));
            rc[rc_len - 1] =
                "ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210"
                "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                [35 + value % base];
            value /= base;
        } while (value);
        rc[rc_len--] = '\0';
        size_t low = 0;
        while (low < rc_len) {
            const char tmp = rc[low];
            rc[low++] = rc[rc_len];
            rc[rc_len--] = tmp;
        }
    }
    return rc;
}

int main(int argc, char *argv[]) {
    pn = argv[0];
    uint8_t out_base = 10;
    un value;
    if (argc > 1) {
        uint8_t in_base = 10;
        char *r_number = NULL;
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "--help")) {
                printf("USAGE:\n\t%s <number> -i <in_base> -o <out_base>\n",
                       argv[0]);
                return 0;
            }

            if (!strcmp(argv[i], "-i")) {
                if (!(++i < argc)) goto incomplete_argument;
                in_base = atoi(argv[i], 10);
                continue;
            }

            if (!strcmp(argv[i], "-o")) {
                if (!(++i < argc)) goto incomplete_argument;
                out_base = atoi(argv[i], 10);
                continue;
            }

            if (r_number == NULL) {
                r_number = argv[i];
                continue;
            }

            fprintf(stderr, "%s: unknown argument: \"%s\"\n",
                    argv[0], argv[i]);
            return 1;

          incomplete_argument:
            fprintf(stderr, "%s: argument \"%s\" requires a value\n",
                    argv[0], argv[i - 1]);
            return 1;
        }

        if (r_number == NULL) {
          noargs:
            fprintf(stderr, "%s: run with \"--help\" for usage.\n", argv[0]);
            return 1;
        }
        value = atoi(r_number, in_base);
    } else
        goto noargs;
    {
        char *const s = itoa(value, out_base);
        printf("%s\n", s);
        free(s);
    }
    return 0;
}
