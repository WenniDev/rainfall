unsigned int language;

int  greetuser(char src)
{
  char	*dest; // [esp+10h] [ebp-48h] BYREF
  char	*v3; // [esp+20h] [ebp-38h]
  char	v4; // [esp+22h] [ebp-36h]

  switch ( language )
  {
    case 1:
      dest = xmmword_8048717;
      v3 = *((_WORD *)&xmmword_8048717 + 8);
      v4 = *((_BYTE *)&xmmword_8048717 + 18);
      break;
    case 2:
      strcpy(&dest, "Goedemiddag! ");
      break;
    case 0:
      strcpy(dest, "Hello ");
      break;
  }
  strcat(dest, &src);
  return puts(dest);
}

int main(int argc, const char **argv)
{
	char buf[76];
	char dest[76];
	char *lang;

	if (argc != 3)
		return 1;

	memset(dest, 0, sizeof(dest));
	strncpy(dest, argv[1], 40);
	strncpy(&dest[40], argv[2], 32);

	lang = getenv("LANG");
	if (lang)
	{
		if (memcmp(lang, "fi", 2) == 0) {
			language = 1;
		}
		else if (memcmp(lang, "nl", 2) == 0) {
			language = 2;
		}
	}

	memcpy(buf, dest, sizeof(buf));
	
	greetuser(buf[0]);
	return 0;
}