a simple example of a program that was made to create a massive set of
insert statements to populate a database with some values. The script also made a bunch of fake files in the temp directory. You pump the output to a file and then capture stdout and stderr , run the stderr file as  absh script to create bogus files. source the stdout file in mysql to insert the sql into the table. This was used to make some test data for a system that had to purge data in a table as well as files the database had refered to.

