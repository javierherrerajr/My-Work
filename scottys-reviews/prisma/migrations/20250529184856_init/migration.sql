-- CreateTable
CREATE TABLE "User" (
    "id" TEXT NOT NULL,
    "netid" TEXT,
    "username" TEXT,
    "password" TEXT,
    "resetToken" TEXT,
    "resetTokenExpiry" TIMESTAMP(3),
    "status" TEXT,
    "expectedGradYear" INTEGER,
    "major" TEXT,
    "aboutMe" TEXT,
    "avatar" TEXT,

    CONSTRAINT "User_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Class" (
    "courseid" TEXT NOT NULL,
    "classname" TEXT NOT NULL,
    "units" INTEGER NOT NULL,
    "subject" TEXT,

    CONSTRAINT "Class_pkey" PRIMARY KEY ("courseid")
);

-- CreateTable
CREATE TABLE "Review" (
    "reviewid" SERIAL NOT NULL,
    "review" TEXT,
    "ta" TEXT,
    "rating" INTEGER,
    "quarter" TEXT,
    "professor" TEXT,
    "netid" TEXT,
    "userId" TEXT NOT NULL,
    "courseid" TEXT NOT NULL,

    CONSTRAINT "Review_pkey" PRIMARY KEY ("reviewid")
);

-- CreateIndex
CREATE UNIQUE INDEX "User_netid_key" ON "User"("netid");

-- AddForeignKey
ALTER TABLE "Review" ADD CONSTRAINT "Review_userId_fkey" FOREIGN KEY ("userId") REFERENCES "User"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Review" ADD CONSTRAINT "Review_courseid_fkey" FOREIGN KEY ("courseid") REFERENCES "Class"("courseid") ON DELETE RESTRICT ON UPDATE CASCADE;
