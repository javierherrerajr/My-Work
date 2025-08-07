
const { PrismaClient } = require("@prisma/client");
const fs = require("fs");
const path = require("path");
const csv = require("csv-parser");

const prisma = new PrismaClient();

function normalizeCourseId(id) {
  return String(id).replace(/\s+/g, "").toUpperCase();
}

async function readCSV(filePath) {
  const rows = [];
  return new Promise((resolve, reject) => {
    fs.createReadStream(filePath)
      .pipe(csv())
      .on("data", (data) => rows.push(data))
      .on("end", () => resolve(rows))
      .on("error", reject);
  });
}

async function main() {
  const classCsvPath = path.join(__dirname, "classes.csv");
  const reviewCsvPath = path.join(__dirname, "ucr_cleaned.csv");

  // Seed Class table
  if (fs.existsSync(classCsvPath)) {
    const classRows = await readCSV(classCsvPath) as Array<Record<string, any>>;
    for (const row of classRows) {
      const courseid = normalizeCourseId(row.courseid);
      await prisma.class.upsert({
        where: { courseid },
        update: {},
        create: {
          courseid,
          classname: String(row.classname).trim(),
          subject: row.subject?.trim() || null,
          units: parseInt(row.units),
        },
      });
    }
    console.log(`✅ Seeded ${classRows.length} classes`);
  } else {
    console.warn("⚠️ classes.csv not found — skipping class seeding.");
  }

  // Create default anon user
  const defaultUser = await prisma.user.upsert({
    where: { netid: "anon" },
    update: {},
    create: {
      netid: "anon",
      username: "Anonymous",
      password: null,
      status: "NA",
      expectedGradYear: null,
      major: "Undeclared",
      aboutMe: null,
    },
  });

  // Seed Review table
  if (fs.existsSync(reviewCsvPath)) {
    const reviewRows = await readCSV(reviewCsvPath) as Array<Record<string, any>>;
    for (const row of reviewRows) {
      const courseid = normalizeCourseId(row.courseid);
      const exists = await prisma.class.findUnique({ where: { courseid } });
      if (!exists) { // This line was meant for testing seeding of classes: console.warn(`❌ Course not found for review with courseid: ${courseid}. Dropping this review.`);
        continue;
      }

      await prisma.review.create({
        data: {
          userId: defaultUser.id,
          netid: defaultUser.netid,
          courseid,
          review: String(row.review).trim(),
          rating: parseInt(row.rating),
          quarter: String(row.quarter).trim(),
          professor: String(row.professor).trim(),
          ta: String(row.ta).trim(),
        },
      });
    }
    console.log(`✅ Seeded ${reviewRows.length} reviews`);
  } else {
    console.warn("⚠️ ucr_cleaned.csv not found — skipping review seeding.");
  }
}

main()
  .catch((e) => {
    console.error("❌ Seeding error:", e);
    process.exit(1);
  })
  .finally(async () => {
    await prisma.$disconnect();
  });
