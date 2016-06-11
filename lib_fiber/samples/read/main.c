#include "lib_acl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fiber/lib_fiber.h"

static void fiber_io(FIBER *fiber acl_unused, void *ctx acl_unused)
{
	int   ret;
	char  buf[8192];

	printf("please input: ");
	fflush(stdout);

	ret = read(0, buf, sizeof(buf) - 1);

	if (ret > 0) {
		const char *prompt = "your input: ";

		buf[ret] = 0;
		//printf("read: [%s]\r\n", buf);

		if (write(1, prompt, strlen(prompt)) != (int) strlen(prompt))
			printf("write error: %s\r\n", acl_last_serror());
		else if (write(1, buf, strlen(buf)) != (int) strlen(buf))
			printf("write to stdout error: %s\r\n",
				acl_last_serror());
	} else
		printf("read error: %s\r\n", acl_last_serror());

	fiber_io_stop();
}

int main(void)
{
	fiber_create(fiber_io, NULL, 320000);
	fiber_schedule();

	return 0;
}
