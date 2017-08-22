
#include <stdio.h>
#include "mpp_cpplib.h"
#include "mpp_config.h"

extern char *getenv();

char *progname;

cpp_reader parse_in;
cpp_options options;

/* More 'friendly' abort that prints the line and file.
   mpp_config.h can #define abort fancy_abort if you like that sort of thing.  */
void fancy_abort () { fatal("Internal mpp abort."); }

int main(int argc, char **argv)
{
  char *p;
  int i;
  int argi = 1;
  struct cpp_options *opts = &options;

  p = argv[0] + strlen (argv[0]);
  while (p != argv[0] && p[-1] != '/') --p;
  progname = p;

  init_parse_file (&parse_in);
  parse_in.data = opts;

  init_parse_options (opts);
  
  argi += cpp_handle_options (&parse_in, argc - argi , argv + argi);
  if (argi < argc)
    fatal ("Invalid option `%s'", argv[argi]);
  parse_in.show_column = 1;

  i = push_parse_file (&parse_in, opts->in_fname);
  if (i != SUCCESS_EXIT_CODE)
    return i;

  /* Now that we know the input file is valid, open the output.  */

  if (!opts->out_fname || !strcmp (opts->out_fname, ""))
    opts->out_fname = "stdout";
  else if (! freopen (opts->out_fname, "w", stdout))
    cpp_pfatal_with_name (&parse_in, opts->out_fname);

  for (;;)
    {
      enum cpp_token kind;
      if (! opts->no_output)
	{
	  fwrite (parse_in.token_buffer, 1, CPP_WRITTEN (&parse_in), stdout);
	}
      parse_in.limit = parse_in.token_buffer;
      kind = cpp_get_token (&parse_in);
      if (kind == CPP_EOF)
	break;
    }

  cpp_finish (&parse_in);

  if (parse_in.errors)
    exit (FATAL_EXIT_CODE);
  exit (SUCCESS_EXIT_CODE);
}

/*EOF*/

