/**
 * @file
 *
 * @date Jun 6, 2014
 * @author: Anton Bondarev
 */

#include <stdio.h>
#include <stdlib.h>

#include <embox/cmd.h>

EMBOX_CMD(dev_access_main);

static int dev_access_main(int argc, char *argv[]) {
	char *str = "Данные, которые будут отправлены в терминал";

	if (argc != 3)
	{
		printf("не правильное количество аргументов \n");
		printf("tty_access терминал_1 терминал_2 \n");

		return 0;
	}

	///////////////////////////////////////////// Открываем терминал 1 для записи
	if ((freopen(argv[1], "w", stdout)) == NULL )
	{
		fprintf(stderr, "Не удалось открыть терминал %s \n", argv[1]);
	}
	else
	{
		printf("%s \n", str);
		fclose(stdout);
		fprintf(stderr, "Данные успешно записаны в терминал %s\n", argv[1]);
	}

///////////////////////////////////////////// Открываем терминал 2 для записи
	if ((freopen(argv[2], "w", stdout)) == NULL )
	{
		fprintf(stderr, "Не удалось открыть терминал %s \n", argv[2]);
		exit(1);
	}
	else
	{
		printf("%s \n", str);
		fclose(stdout);
		fprintf(stderr, "Данные успешно записаны в терминал %s\n", argv[2]);
	}

	return 0;
}
