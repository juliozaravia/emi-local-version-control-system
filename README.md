# **Emi Personal Control Version System**

## **1. What is Emi and what is it for?**
Emi is an application developed to learn and practice the use of the C ++ programming language.

**Emi allows the user to capture and save versions of files that are constantly modified, preserving different states of the file (or group of files) over time**. Emi also allows you to view the groups of files captured over time and restore them in order to be able to recover any previous state of the file (or group of files) in the event of any incident or unforeseen event.

## **2. How should I install Emi?**
Because Emi is (still) a humble prototype made for learning purposes, I have not included an executable version. Instead, **I have included a Makefile that you can adapt to your needs and generate the respective binary**. If you do not know how to use a Makefile, here are three extraordinary resources:
- [Playlist (in Spanish) of an extraordinary YouTube channel where I found a complete tutorial on Make / Makefile.](https://www.youtube.com/playlist?list=PLTd5ehIj0goOrqKZPvq1Np-8PUFcQSSm- "Complete Playlist (in Spanish) of an extraordinary YouTube channel where I found a complete tutorial on Make / Makefile.")
- [Tutorial with basic concepts for using a Makefile.](https://www.youtube.com/watch?v=aw9wHbFTnAQ "Tutorial with basic concepts for using a Makefile.")
- [And, if you want to delve into the subject, it is best to read the official documentation.](https://www.gnu.org/software/make/manual/make.html "And, if you want to delve into the subject, it is best to read the official documentation.")

**Note:** *Obviously, if you use an IDE, this procedure is already covered and will depend on the respective IDE.*

Once the executable is generated, I advise you to create the environment variable so that you can invoke Emi from any location within your system. **We will see this in more detail in the next block.**

## **3. How is Emi used?**
### Setting the environment variable.
Initially Emi was programmed to work on the Windows operating system, however, later I migrated to using Linux so I have tried to make the application as compatible as possible between both operating systems.

Emi is a program that by concept should work from any location within your system, for this to be possible, it is highly recommended to configure the path of the Emi executable file as a system environment variable. **If you still do not know how to configure an environment variable, here are some links that helped me a lot**:
- For Windows: https://www.youtube.com/watch?v=sXW2VLrQ3Bs
- For Windows: https://www.youtube.com/watch?v=Y2q_b4ugPWk
- For Linux: https://www.youtube.com/watch?v=pjh9rU9h22Q
- For Linux: https://www.youtube.com/watch?v=Y6_7xaxkPik

### Use of Emi commands.
After setting the environment variable you can access the location (path) of the files you want to track. Once there you can use the commands to execute the operations provided by Emi. **Copying the commands and the description of each of them would make this document very extensive, so I will leave a link to another document that contains the details of all the commands supported by Emi:**
- [Emi Command List.](https://github.com/juliozaravia/emi-local-version-control-system/blob/main/EMI_COMMAND_LIST.md "Emi Command List.")

Additionally, if you have already set the environment variable on your system, **you can simply enter the command: `emi --help` from any location, to see a list of all allowed commands and how they are used.** Here's an example:

![Help Command](http://www.juliozaravia.com/git-images/help_command.jpg "Help Command")

## 4. **What stage of development is Emi in?**
Emi is a project that started to strengthen my learning in the C++ language. For this reason, currently, the application only supports the [basic operations listed here](https://github.com/juliozaravia/emi-local-version-control-system/blob/main/EMI_COMMAND_LIST.md "basic operations listed here").

**I will be constantly updating this repository and adding complementary functionalities**, and I inform those interested in improving this project that you can make the modifications or improvements that you deem appropriate.

**I also recommend C++ learners (like me) to review the code,** I have tried as much as possible to use the most basic structures and program everything in a simple way that makes it easy to read, review and learn.

There is a lot **(A LOT)** to optimize in this project, however **I think it can be very helpful for a beginner to review another beginner's coding and identify what has been implemented well and what needs improvement.**

## **5. Do you want to optimize this humble project??**
I appreciate your interest. If you are willing to optimize this project, here are some recommendations that I will implement myself. **Let's see who does it the fastest :)**.
- [What can we improve on Emi?](https://github.com/juliozaravia/emi-local-version-control-system/blob/main/PROPOSED_IMPROVEMENTS.md "What can we improve on Emi?")

## **6. Anything else?**
- All constructive criticisms are very well received, you can send them to me at hey@juliozaravia.com.
- If you are going to criticize this project in an offensive way, please don't do it, remember that **no one comes to this world knowing everything**.
- If you want to improve the code, you are free to do so, **just let me know what you changed or improved so I can learn from you**.
- I know, my English is poor. I am working on it too. Thanks for understand.
- That's it, I really enjoyed working on this version, if you took the time to read this, you are a good person and **I wish you a good day**.
