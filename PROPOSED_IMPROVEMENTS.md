## **General List of Proposed Improvements**
**Note: ** *It is a bad idea to read this file before reading the README.md file. Read the README.md file to get context.*

- **Schedule an error log**. Every time an error prevents Emi from working, the error message should be recorded in a log, along with the date and time of the event.
- **Restore bot**. When an error occurs, it is likely that it affects the files that are being processed. There should be a bot that is in charge of checking if the processed files were affected and restoring them so that the operation can continue.
- **Temporary backups**. Many of the Emi operations require modifying, deleting or moving files, while these operations are running a copy of the content and status of the processed files should be made (in the background), in order not to lose information if something breaks.
- There is no function to remove files from the ignore list.
- There is no function to display the list of ignored files.

These are the requirements that seem important to me now. Surely there are many more, **if you have been able to identify more please write to me at hey@juliozaravia.com** and let's talk about that.
